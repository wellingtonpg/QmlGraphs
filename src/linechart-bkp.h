#ifndef LINECHART_H
#define LINECHART_H

#include <QDate>
#include <QPoint>
#include <QColor>
#include <QPointer>
#include <QAbstractItemModel>
#include <QList>

struct LineChartEntry;

/**
 * @author Wellington Palma
 * @brief Implementation of line chart
 */
class LineChart final : public QObject
{
    Q_OBJECT

    //Q_PROPERTY( QAbstractListModel * model READ model WRITE setModel NOTIFY modelChanged )
    Q_PROPERTY(QVector<qreal> x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(QVector<qreal> y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(qreal position READ position WRITE setPosition NOTIFY positionChanged )
    Q_PROPERTY(qreal pageSize READ pageSize WRITE setPageSize NOTIFY pageSizeChanged )
    Q_PROPERTY(QDate startDate READ startDate NOTIFY modelChanged )
    Q_PROPERTY(QDate finalDate READ finalDate NOTIFY modelChanged )
    Q_PROPERTY(int visibleMonths READ visibleMonths NOTIFY visibleMonthsChanged )
    Q_PROPERTY(qreal smallestValue READ smallestValue NOTIFY scaleValuesChanged )
    Q_PROPERTY(qreal topValue READ topValue NOTIFY scaleValuesChanged )
    Q_PROPERTY(bool elapsedMode READ elapsedMode WRITE setElapsedMode NOTIFY elapsedModeChanged )
    Q_PROPERTY(bool verticalGrade READ verticalGrade WRITE setVerticalGrade NOTIFY verticalGradeChanged )
    Q_PROPERTY(QString startFrameDate READ getStartFrameDate NOTIFY pageSizeChanged )
    Q_PROPERTY(QString endFrameDate READ getEndFrameDate NOTIFY pageSizeChanged )

    Q_PROPERTY(QString xLabel READ getXLabel NOTIFY labelChanged )
    Q_PROPERTY(QString yLabel READ getYLabel NOTIFY labelChanged )

    public:
        explicit LineChart(QObject * parent = 0 );
        ~LineChart();

        QVector<double> *x() const { return m_x; }
        void setX(QVector<double> *x);

        QVector<double> *y() const { return m_y; }
        void setY(QVector<double> *y);

        /**
         * @brief Funcao que desenha o LineChart
         * @param [in] Ponteiro p/ QPainter, ponteiro p/ QStyleOptionGraphicsItem, ponteiro p/ QWidget
         */
        void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

        /**
         * @brief Funcao que reimplementa a geometryChanged da classe base QDeclarativeItem
         * @param [in] QRectF: Novo tamanho
         *             QRectF: Tamanho antigo
         * @remarks Funcao chama a QDeclarativeItem::geometryChanged(), reconfigura o LineChart e redesenha o LineChart
         */
        void geometryChanged (const QRectF & newGeometry, const QRectF & oldGeometry);

        /**
         * @brief Funcao que captura e trata o evento de movimento do ponteiro do mouse sobre o LineChart
         * @param [in] QGraphicsSceneHoverEvent: Ponteiro p/ evento
         */
        void hoverMoveEvent(QGraphicsSceneHoverEvent * event);

        /**
         * @brief Funcao que captura e trata o evento de entrada do ponteiro do mouse sobre o LineChart
         * @param [in] QGraphicsSceneHoverEvent: Ponteiro p/ evento
         */
        void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );

        /**
         * @brief Funcao que captura e trata o evento de saída do ponteiro do mouse sobre o LineChart
         * @param [in] QGraphicsSceneHoverEvent: Ponteiro p/ evento
         */
        void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );

        /**
         * @brief Funcao que recupera a data inicial
         * @return QDate: Data inicial
         */
        const QDate startDate() const
        {
            return m_startDate;
        }

        /**
         * @brief Funcao que recupera a data final
         * @return QDate: Data final
         */
        const QDate finalDate() const
        {
            return m_finalDate;
        }

        /**
         * @brief Funcao que recupera o numero de meses apresentados
         * @return int: Numero de meses apresentados
         */
        const int visibleMonths() const
        {
            return m_visibleMonths;
        }

        /**
         * @brief Funcao que recupera a posicao do LineChart
         */
        const qreal position() const
        {
            return m_position;
        }

        /**
         * @brief Funcao que seta a posicao do LineChart
         */
        void setPosition( qreal & position );

        /**
         * @brief Funcao que recupera o tamanho da pagina a ser apresentada
         * @return qreal: Tamanho da pagina
         */
        const qreal pageSize() const
        {
            return m_pageSize;
        }

        /**
         * @brief Funcao que seta o tamanho da pagina a ser apresentada
         * @param [in] qreal: Tamanho da pagina - Range: 0 < tamanho da pagina <= 1.0
         */
        void setPageSize( qreal & pageSize );

        /**
         * @brief Funcao que recupera o maior valor de saldo a ser apresentado
         * @return qreal: Maior valor de saldo a ser apresentado
         */
        const qreal topValue() const
        {
            return m_topValue;
        }

        /**
         * @brief Funcao que recupera o menor valor de saldo a ser apresentado
         * @return qreal: Menor valor de saldo a ser apresentado
         */
        const qreal smallestValue() const
        {
            return m_smallestValue;
        }

        /**
         * @brief Funcao que recupera o status da grade vertical
         * @return bool: Grade vertical habilitada
         */
        const bool verticalGrade() const
        {
            return m_verticalGrade;
        }

        /**
         * @brief Funcao que seta o status da grade vertical
         * @param bool: Grade vertical habilitada
         */
        void setVerticalGrade( const bool & enabled );

        /**
         * @brief Funcao que recupera o status do elapsedMode.
         * @remarks Se "true" mostra o label do LineChart com a data no formato mes/ano.
         */
        const bool elapsedMode() const
        {
            return m_elapsedMode;
        }

        /**
         * @brief Funcao que seta o status do elapsedMode.
         * @remarks Se "true" mostra o label do LineChart com a data no formato mes/ano.
         */
        void setElapsedMode( const bool & enabled );

        /**
         * @brief Funcao que recupera a data inicial no formato "dd/MM/yy"
         * @return QString: Data inicial
         */
        QString getStartFrameDate()
        {
            return m_startDateFrame.toString( "dd/MM/yy" );
        }

        /**
         * @brief Funcao que recupera a data final no formato "dd/MM/yy"
         * @return QString: Data final
         */
        QString getEndFrameDate()
        {
            return m_endDateFrame.toString( "dd/MM/yy" );
        }

    signals:
        /**
         * @brief Sinal que comunica mudanca do model
         */
        void modelChanged();

        /**
         * @brief Sinal que comunica mudanca da posicao atual de apresentacao
         */
        void positionChanged();

        /**
         * @brief Sinal que comunica mudanca do tamanho da pagina de apresentacao
         */
        void pageSizeChanged();

        /**
         * @brief Sinal que comunica mudanca no numero de meses apresentados
         */
        void visibleMonthsChanged();

        /**
         * @brief Sinal que comunica mudanca da escala atual de apresentacao
         */
        void scaleValuesChanged();

        /**
         * @brief Sinal que comunica mudanca da escala atual de apresentacao
         */
        void elapsedModeChanged();

        /**
         * @brief Sinal que comunica mudanca do status da grade vertical
         */
        void verticalGradeChanged();

        /**
         * @brief Sinal que comunica o ponto ativo do grafico
         */
        void pointActivation( const QPoint & point, const QDate & date, bool active );

    private slots:
        /**
         * @brief Funcao slot que processa o novo model configurado
         */
        void modelUpdated();

    private:
        /**
         * @brief Funcao reconfigura o LineChart preparando p/ ser desenhado
         * @remarks - Seta o maior e menor valor de saldo
         *          - Calcula o offset do eixo x
         *          - Determina a range de data(data inicial e final) a ser apresentada pelo LineChart
         *          - Prepara o vetor de poligonos a serem desenhados
         *          - Prepara o map utilizado p/ recuperar a data passando a posicao do eixo x como key
         */
        void reconfigureChart();

        /**
         * @brief Funcao que recupera o ponto de saldo mais proximo da posicao atual do mouse
         * @param [in] QPoint: Posicao atual do mouse
         * @return QPoint: Ponto de saldo mais proximo da posicao atual do mouse
         */
        QPoint findNearestPoint( const QPoint & point ) const;

    private:
        static const int leftOrRightMargem = 20;
        static const int bottomMargem = 16;

        bool m_elapsedMode;
        bool m_verticalGrade;
        int m_axisYOffset;
        int m_groupCount;
        int m_lastX;
        int m_visibleMonths;
        int firstPointOfSubPolygon;
        qreal m_pageSize;
        qreal m_position;
        qreal m_smallestValue;
        qreal m_negativeHeight;
        qreal m_topValue;
        qreal m_positiveHeight;
        QDate m_endDateFrame;
        QDate m_finalDate;
        QDate m_startDate;
        QDate m_startDateFrame;

        /* Hash utilizado para recupar a data passando como entrada a posicao no eixo x */
        QHash<int, QDate> m_entries;

        /* Map utilizado para indexar as datas */
        QMap<QDate, int> m_months;

        /* Map que armazena uma serie de saldos para cada uma das datas */
        QMap<QDate, QVector<qreal> *> m_series;

        /* Map que armazema a posicao no eixo y(valor do saldo) para cada uma das datas */
        QMap<QDate, int> m_posY;

        QPointer<QVector<qreal>> m_x;
        QPointer<QVector<qreal>> m_y;
        QString m_propertyValue;
        QString m_propertyColor;
        QString m_propertyDate;
        QString m_propertyCategory;

        /* Vetor que armazena uma cor para cada grupo */
        QVector<QColor> m_colors;

        /* Armazena os pontos que compoe o poligono */
        QPolygon m_polygon;
};

#endif // LineChart_H
