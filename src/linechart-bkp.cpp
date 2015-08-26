#include "LineChart.h"

#include <QPainter>
#include <QtCore/qmath.h>
#include <QGraphicsSceneMouseEvent>

static qreal findBestStep(qreal maxValue, int N)
{
    qreal result = qCeil( maxValue / N );

    int digits = 0;
    qreal K = result;

    while (K > 10)
    {
        K /= 10;
        digits++;
    }

    int Z = qPow(10, digits);
    return qFloor(result / Z) * Z;
}


LineChart::LineChart(QObject *parent)
    : QObject(parent),
      m_visibleMonths( 0 ),
      m_elapsedMode( false ),
      m_verticalGrade( false ),
      m_propertyValue( "balance" ),
      m_propertyColor( "color" ),
      m_propertyDate( "date" ),
      m_propertyCategory( "id" ),
      m_position( 0 ),
      m_pageSize( 0.5 ),
      m_x(0),
      m_y(0)
{
    //
    // TODO: parent utilizado no QML, pode vir nulo
    //
    setFlag( QGraphicsItem::ItemClipsToShape );
    setFlag( QGraphicsItem::ItemHasNoContents, false );
    setAcceptHoverEvents( true );
}

LineChart::~LineChart()
{
    qDeleteAll(m_series);
}

void LineChart::setElapsedMode(const bool & enabled)
{
    if (m_elapsedMode != enabled)
    {
        m_elapsedMode = enabled;
        emit elapsedModeChanged();
    }
}

void LineChart::setVerticalGrade(const bool & enabled)
{
    if ( m_verticalGrade != enabled )
    {
        m_verticalGrade = enabled;
        emit verticalGradeChanged();
    }
}

void LineChart::hoverEnterEvent( QGraphicsSceneHoverEvent * event )
{
    Q_ASSERT( event );

    QPoint point( findNearestPoint( event->pos().toPoint() ) );
    const QDate date( m_entries.value( point.x(), QDate() ) );

    point.setY( m_posY.value( date ) );

    m_lastX = point.x();
    emit pointActivation( point, date, !date.isNull() );
}

void LineChart::hoverMoveEvent( QGraphicsSceneHoverEvent * event )
{
    Q_ASSERT( event );

    QPoint point( findNearestPoint( event->pos().toPoint() ) );
    const QDate date( m_entries.value( point.x(), QDate() ) );

    point.setY( m_posY.value( date ) );

    if ( point.x() != m_lastX )
    {
        m_lastX = point.x();
        emit pointActivation( point, date, !date.isNull() );
    }
}

void LineChart::hoverLeaveEvent( QGraphicsSceneHoverEvent * event )
{
    Q_UNUSED( event )

    emit pointActivation( QPoint(), QDate(), false );
}

QPoint LineChart::findNearestPoint( const QPoint & point ) const
{
    if ( m_polygon.isEmpty() )
    {
        return QPoint();
    }

    QPoint nearestPoint;

    // distance will be always less than width + height
    qreal minimumDistance = width() + height();

    foreach ( const QPoint & localPoint, m_polygon )
    {
        // ignore points outside visible area
        if ( localPoint.x() < 0 || localPoint.x() > width() )
        {
            continue;
        }

        qreal distance  = QLineF( localPoint.x(), height(), point.x(), height() ).length();

        if ( distance < minimumDistance )
        {
            nearestPoint = localPoint;
            minimumDistance = distance;
        }
    }

    nearestPoint.setY( 0 );
    return nearestPoint;
}

void LineChart::geometryChanged( const QRectF & newGeometry, const QRectF & oldGeometry )
{
    QDeclarativeItem::geometryChanged( newGeometry, oldGeometry );
    reconfigureChart();
}

void LineChart::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    Q_UNUSED( option )
    Q_UNUSED( widget )

    if ( m_groupCount == 0 )
    {
        return;
    }

    QFont font( "Arial" );
    font.setPixelSize( 10 );
    font.setBold( true );
    QFontMetrics metrics( font );

    painter->setFont( font );
    painter->setPen( Qt::black );
    painter->setRenderHints( QPainter::Antialiasing, true );

    const int count = m_x.count();
    const QColor background( 100, 100, 100, 60 );
    const QList<QDate> & months = m_months.keys();

    for ( int i = 0; i < count; i++ )
    {
        const QDate & dt = months.at( i );
        const int ix = m_months.value( dt );

        int _maxWidth = width() - leftOrRightMargem;

        // just fill even months
        if ( dt.month() % 2 == 0 )
        {
            int fx;

            if ( i >= count - 1 )
            {
                fx = width();
            }

            else
            {
                fx = m_months.value( months.at( i + 1 ) );
            }

            int _ix = ix;

            if( _ix < leftOrRightMargem )
            {
                _ix = leftOrRightMargem;
            }

            int _width = fx - _ix;

            if( _width + _ix > _maxWidth )
            {
                _width = _maxWidth - _ix;
            }

            if ( _width < 0 )
            {
                continue;
            }

            painter->fillRect( _ix, 0, _width, height() - bottomMargin, background );
        }

        int textHeight;
        int startText;

        if ( !m_elapsedMode )
        {
            QRect textSize = painter->fontMetrics().boundingRect( dt.toString( "MMM/yy" ).toUpper() );
            textHeight = textSize.height();
            startText = ix - textSize.width() / 2;

            if ( ( startText >= 0 ) && ( startText <= _maxWidth ) )
            {
                painter->drawText( startText, height() - textHeight + 10, dt.toString( "MMM/yy" ).toUpper() );
            }
        }

        else
        {
            const QString & dayText = QString::number( m_startDate.daysTo( dt ) );
            QRect textSize = painter->fontMetrics().boundingRect( dayText );
            textHeight = textSize.height();
            startText = ix - textSize.width() / 2;

            if ( startText >= 0 &&  startText <= _maxWidth )
            {
                painter->drawText( startText, height() - textHeight + 10, dayText );
            }
        }
    }

    if ( m_verticalGrade )
    {
        int w = width();
        int h = height();
        qreal step = findBestStep( m_topValue, 6 );
        qreal value = step;

        while ( value <= m_topValue )
        {
            int py = ( h - bottomMargem ) * ( 1.0 - ( value / m_topValue ) );
            painter->fillRect( 0, py - 1, w, 1, Qt::white );
            value += step;
        }
    }

    painter->setPen( Qt::white );

    QTransform transform;
    transform.translate( 0, m_axisYOffset );
    QTransform reverseTransform;
    reverseTransform.translate( 0, -m_axisYOffset );

    painter->setTransform( transform, true );

    painter->setBrush( m_colors[0] );
    painter->drawPolygon( m_polygon );

    painter->setTransform( reverseTransform, true );
}

void LineChart::setX( QVector<qreal> x )
{
    Q_ASSERT(x);

    QVector<qreal> newModel = qobject_cast<QVector<qreal>>(x);

    //Q_ASSERT( newModel );
    if ( !newModel )
    {
        qCritical( ) << __FILE__ << ":" << __LINE__ << " : " << "erro no casting.";
        return;
    }

    if ( newModel == m_model )
    {
        return;
    }

    if ( m_model )
    {
        disconnect( m_model, SIGNAL( rowsInserted( const QModelIndex &, int, int ) ), this, SLOT( modelUpdated() ) );
        disconnect( m_model, SIGNAL( rowsRemoved( const QModelIndex &, int, int ) ), this, SLOT( modelUpdated() ) );
        disconnect( m_model, SIGNAL( dataChanged( const QModelIndex &, const QModelIndex & ) ), this, SLOT( modelUpdated() ) );
    }

    m_model = newModel;

    if ( m_model )
    {
        connect( m_model, SIGNAL( rowsInserted( const QModelIndex &, int, int ) ), this, SLOT( modelUpdated() ) );
        connect( m_model, SIGNAL( rowsRemoved( const QModelIndex &, int, int ) ), this, SLOT( modelUpdated() ) );
        connect( m_model, SIGNAL( dataChanged( const QModelIndex &, const QModelIndex & ) ), this, SLOT( modelUpdated() ) );
    }

    modelUpdated();
    emit modelChanged();
}

void LineChart::setPosition( qreal & position )
{
    /*
     * Se a posicao e:
     * - maior que 0.0 e menor que 1.0: posicao igual a ela mesmo
     * - menor que 0.0: posicao igual a 0.0
     * - maior que 1.0: posicao igual a 1.0
     */
    position = qBound<qreal>( 0.0, position, 1.0 );

    /* Se a nova posicao e diferente do atual, seta a posicao e reconfigura o grafico */
    if ( !qFuzzyCompare( m_position, position ) )
    {
        m_position = position;
        reconfigureChart();
        emit positionChanged();
    }
}

void LineChart::setPageSize( qreal & pageSize )
{
    /*
     * Se o tamanho da pagina e:
     * - maior que 0.0 e menor que 1.0: tamanho da pagina igual a ele mesmo
     * - menor que 0.0: tamanho da pagina igual a 0.0
     * - maior que 1.0: tamanho da pagina igual a 1.0
     */
    pageSize = qBound<qreal>( 0.0, pageSize, 1.0 );

    /* Se o novo tamanho da pagina e diferente do atual, seta o tamanho da pagina e reconfigura o grafico */
    if ( !qFuzzyCompare( m_pageSize, pageSize ) )
    {
        m_pageSize = pageSize;
        reconfigureChart();
        emit pageSizeChanged();
    }
}

void LineChart::modelUpdated()
{
    /* Bloco que reseta variaveis de escopo de classe */
    qDeleteAll( m_series );

    m_series.clear();
    m_entries.clear();
    m_colors.clear();

    m_groupCount = 0;
    m_startDate = QDate();
    m_finalDate = QDate();

    /* Se nao existir model setado, chama a funcao que desenha o LineChart com a configuracao antiga */
    if ( !m_model )
    {
        update();
        return;
    }

    /* Seta as variáveis locais utilizadas para recuperar as informacoes do model */
    int count = m_model->rowCount();
    int dateRole = m_model->roleNames().key( m_propertyDate.toLatin1() );
    int valueRole = m_model->roleNames().key( m_propertyValue.toLatin1() );
    int colorRole = m_model->roleNames().key( m_propertyColor.toLatin1() );
    int categoryRole = m_model->roleNames().key( m_propertyCategory.toLatin1() );

    QHash<int, int> groups;

    /* Vare todas os registros do model  e cria o hash que indexa os IDs dos grupos contidos no model */
    for ( int row = 0; row < count; row++ )
    {
        const QModelIndex & index = m_model->index( row, 0 );
        const int id = m_model->data( index, categoryRole ).toInt();

        if ( !groups.contains( id ) )
        {
            groups.insert( id, groups.count() );
        }
    }

    /* Seta os valores para containers de escopo de classe */
    m_groupCount = groups.count();
    m_colors.resize( m_groupCount );

    /* Vare todas os registros do model e cria as series de saldos */
    for ( int row = 0; row < count; row++ )
    {
        const QModelIndex & index = m_model->index( row, 0 );
        const int id = m_model->data( index, categoryRole ).toInt();

        if ( !groups.contains( id ) )
        {
            continue;
        }

        /* Seta o index do ID do grupo */
        const int group = groups.value( id );

        /* Seta a data e valor de saldo recuperado do registro atual do model apontado pelo QModelIndex */
        const QDate & date = m_model->data( index, dateRole ).toDate();
        const qreal value = m_model->data( index, valueRole ).toReal();

        /* Adiciona a cor do grupo em questao a lista de cores */
        m_colors[group] = m_model->data( index, colorRole ).value<QColor>();

        /* Recupera o ponteiro para o vetor de valores de saldo, caso o mesmo exista um para a data atual passada como parametro no map de series  */
        QVector<qreal> * block = m_series.value( date, 0 );

        /* Adiciona a data atual no map de series */
        if ( !block )
        {
            block = new( __FILE__, __LINE__ ) QVector<qreal>( m_groupCount, 0 );
            m_series.insert( date, block );
        }

        /* Seta data inicial */
        if ( date < m_startDate || m_startDate.isNull() )
        {
            m_startDate = date;
        }

        /* Seta data final */
        if ( date > m_finalDate || m_finalDate.isNull() )
        {
            m_finalDate = date;
        }

        /* Insere valor do saldo para o grupo em questao */
        block->insert( group, value );
    }

    reconfigureChart();
}

void LineChart::reconfigureChart()
{
    /* Se o LineChart nao estiver sendo apresentado ele nao e reconfigurado */
    if ( width() == 0 || height() == 0 )
    {
        return;
    }

    /* Limpa o map que armazena as datas do historico */
    m_months.clear();

    m_polygon.clear();

    /* Reseta o os valores maximos e minimos de saldo  */
    int topValue = 0;
    int smallestValue = 0;

    int totalDays = m_startDate.daysTo( m_finalDate );
    int remainingDays = totalDays * ( 1.0 -  m_pageSize );

    m_startDateFrame = m_startDate.addDays( m_position * remainingDays );
    m_endDateFrame = m_startDateFrame.addDays( totalDays - remainingDays );

    int totalFrameDays = m_startDateFrame.daysTo( m_endDateFrame );

    QDate iDate = m_startDate;
    QDate fDate = m_finalDate;

    /* Seta lista de datas que compoe a hash de series */
    const QList<QDate> & keys = m_series.keys();

    /* Seta os valor maximo e minimo de saldo e a data inicial e final do frame a ser apresentado, caso nao exista nenhum registro no map de series */
    if ( !keys.empty() )
    {
        topValue = m_series.value( keys.at( 0 ) )->at( 0 );
        smallestValue = m_series.value( keys.at( 0 ) )->at( 0 );
    }

    /* Seta a data inicial e final do frame de apresentacao atual */
    foreach ( const QDate & date, keys )
    {
        if ( date <= m_startDateFrame && date > iDate )
        {
            iDate = date;
        }

        if ( date >= m_endDateFrame && date < fDate )
        {
            fDate = date;
        }
    }

    /* Busca pelo maior e menor valor de saldo levando em cosideracao a soma dos valores de saldo de todos os grupos na mesma data */
    foreach ( const QDate & date, keys )
    {
        /* Recupera o saldo de cada grupo para a data atual */
        QVector<qreal> * values = m_series.value( date );

        qreal sum = 0;

        /* Faz a soma de saldo e verifica se ela e ou nao o maior ou menor saldo */
        for ( int i = 0; i < values->count(); i++ )
        {
            sum += values->at( i );

            if ( sum > topValue )
            {
                topValue = sum;
            }

            if ( sum < smallestValue )
            {
                smallestValue = sum;
            }
        }
    }

    /* Caso exista uma mudanca no maior ou menor saldo, reconfigura a escala de valores de saldo do eixo y */
    if ( m_topValue != topValue || m_smallestValue != smallestValue )
    {
        m_topValue = topValue;
        m_smallestValue = smallestValue;
        emit scaleValuesChanged();
    }

    /* Seta a largura util do LineChart tirando as margens esquerda e direita */
    int w = width() - 2 * leftOrRightMargem;

    /* Seta a altura util do LineChart tirando a margem inferior */
    int h = height() - bottomMargem;

    /* Calculo da altura maxima dos saldos positivos e negativos, e do offset do eixo y */
    qreal rangeValues = m_topValue - m_smallestValue;

    /* Trata a possivel divisao por zero, caso a range de valores seja igual a zero */
    if ( rangeValues != 0 && m_smallestValue * m_topValue < 0 )
    {
        m_negativeHeight = h * ( m_smallestValue / rangeValues );
        m_positiveHeight = h * ( m_topValue / rangeValues );
    }

    else
    {
        m_negativeHeight = 0;
        m_positiveHeight = h;
    }

    m_axisYOffset = m_positiveHeight;

    /* Declaracao das variaveis locais usados na criacao de cada poligono */
    int lastPx;
    int lastPy;
    int px = 0;
    int py = 0;
    qreal lastSum;
    qreal sum = 0;
    QPoint initialPoint;
    QPoint newPoint;

    /* Cria o primeiro e último ponto do poligono */
    m_polygon << QPoint( w + leftOrRightMargem, 0 );
    m_polygon << QPoint( leftOrRightMargem, 0 );

    /* Cria um poligono para cada um dos grupos */
    foreach ( const QDate & date, keys )
    {
        /* Nao cria os poligonos para as datas fora da range de data inicial e final */
        if ( date < iDate || date > fDate )
        {
            continue;
        }

        qreal offset = m_startDateFrame.daysTo( date );
        QVector<qreal> * values = m_series.value( date );

        lastPx = px;
        px  = ( ( offset / totalFrameDays ) * w ) + leftOrRightMargem;

        m_entries.insert( px, date );

        lastSum = sum;
        sum = 0;

        /* Soma o valor de saldo de todos os grupos da data em questao */
        for ( int i = 0; i < values->count(); i++ )
        {
            sum += values->at( i );
        }

        lastPy = py;

        /*
         *  Py e positivo para saldos negativos e negativo para os saldos positivos para adequar ao sistema de coordenadas.
         *  O maximo valor de saldo deve ocupar apenas 90% do canvas.
         */
        if ( sum < 0 )
        {
            py = m_negativeHeight * ( sum / m_smallestValue ) * 0.90 * ( -1 );
        }

        else
        {
            py = m_positiveHeight * ( sum / m_topValue ) * 0.90 * ( -1 );
        }

        int popUpPy;

        popUpPy = py + m_axisYOffset;

        m_posY.insert( date, popUpPy );

        m_polygon << QPoint( px, py );
    }

    qreal a, b;

    if ( m_polygon.at( 2 ).x() < leftOrRightMargem )
    {
        qreal firstX = m_polygon.at( 2 ).x();
        qreal firstY = m_polygon.at( 2 ).y();
        qreal secondX = m_polygon.at( 3 ).x();
        qreal secondY = m_polygon.at( 3 ).y();

        /* Calculo da equacao da reta */
        a = ( secondY - firstY ) / ( secondX - firstX );
        b = firstY - ( a * firstX );

        newPoint.setY( a * leftOrRightMargem + b  );
        newPoint.setX( leftOrRightMargem );

        m_polygon.replace( 2, newPoint );
    }

    if ( m_polygon.last().x() > w + leftOrRightMargem )
    {
        qreal penultimo = m_polygon.count() - 2;
        qreal xPenultimo = m_polygon.at( penultimo ).x();
        qreal yPenultimo = m_polygon.at( penultimo ).y();
        qreal lastX = m_polygon.last().x();
        qreal lastY = m_polygon.last().y();

        /* Calculo da equacao da reta */
        a = ( lastY - yPenultimo ) / ( lastX - xPenultimo );
        b = yPenultimo - ( a * xPenultimo );

        newPoint.setY( a * ( w + leftOrRightMargem ) + b );
        newPoint.setX( w + leftOrRightMargem );

        m_polygon.replace( m_polygon.count() - 1, newPoint );
    }

    /* Armazena as datas visiveis */
    int visibleMonthCount = 0;
    int fi = iDate.year() * 100 + iDate.month();
    int ff = fDate.year() * 100 + fDate.month();

    while ( fi <= ff )
    {
        int year = fi / 100;
        int month = fi % 100;

        QDate date( year, month, 1 );

        qreal d1 = m_startDateFrame.daysTo( date );
        qreal ix = ( d1 / totalFrameDays ) * w;
        m_months.insert( date, ix + leftOrRightMargem );

        fi = ( month < 12 ) ? ( fi + 1 ) : ( ( year + 1 ) * 100 + 1 );
    }

    visibleMonthCount = m_startDateFrame.daysTo( m_endDateFrame ) + 1;

    if ( m_visibleMonths != visibleMonthCount )
    {
        m_visibleMonths = visibleMonthCount;
        emit visibleMonthsChanged();
    }

    update();
}

