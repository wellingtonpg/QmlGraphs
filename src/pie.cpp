#include "pie.h"

Pie::Pie(QQuickPaintedItem *parent) :
    BaseGraph(parent),
    m_showSeparator(false),
    m_showShadow(false),
    m_showCenterColor(false),
    m_centerColor(255, 255, 255)
{
    updateOverlayer();
}

Pie::~Pie()
{
    delete m_model;
}

PieModel* Pie::model() const
{
    return m_model;
}

void Pie::setModel(PieModel *model)
{
    Q_ASSERT(model);
    if (model != m_model)
    {
        m_model = model;
        emit modelChanged();
        update();
    }
}

bool Pie::showSeparator() const
{
    return m_showSeparator;
}

void Pie::setShowSeparator(bool showSeparator)
{
    if (showSeparator != m_showSeparator)
    {
        m_showSeparator = showSeparator;
        emit showSeparatorChanged();
    }
}

bool Pie::showShadow() const
{
    return m_showShadow;
}

void Pie::setShowShadow(bool showShadow)
{
    if (showShadow != m_showShadow)
    {
        m_showShadow = showShadow;
        emit showShadowChanged();
    }
}

bool Pie::showCenterColor() const
{
    return m_showCenterColor;
}

void Pie::setShowCenterColor(bool showCenterColor)
{
    if (showCenterColor != m_showCenterColor)
    {
        m_showCenterColor = showCenterColor;
        emit showCenterColorChanged();
        updateOverlayer();
    }
}

QColor Pie::centerColor() const
{
    return m_centerColor;
}

void Pie::setCenterColor(QColor centerColor)
{
    if (centerColor != m_centerColor)
    {
        m_centerColor = centerColor;
        emit centerColorChanged();
    }
}

void Pie::paint(QPainter *painter)
{
    Q_ASSERT(painter);

    BaseGraph::paint(painter);

    QRectF graphRect = BaseGraph::boundingRect();

    qreal currentAngle = 90;
    for (unsigned int i = 0; i < m_model->sliceCount(); ++i)
    {
        Slice *slice = m_model->slice(i);
        qreal spanAngle = -360 * (slice->value() / 100.0);
        paintPiece(painter, graphRect, currentAngle, spanAngle, slice->color());
        currentAngle += spanAngle;
    }

    // Draw shadow
    if (m_showShadow)
    {
        painter->drawPixmap(graphRect.toRect(), this->overlayer());
    }

    // Draw center
    if (m_showCenterColor)
    {
        painter->setBrush(m_centerColor);
        QRectF rect = graphRect;
        rect.adjust(rect.width() * 0.25,
                    rect.height() * 0.25,
                    rect.width() * -0.25,
                    rect.height() * -0.25);
        painter->drawPie(rect, 0 * 16, 360 * 16);
    }
}

void Pie::paintPiece(QPainter *painter, const QRectF &rect, qreal startAngle, qreal spanAngle, const QColor &color)
{
    Q_ASSERT(painter);

    painter->setBrush(color);
    if (m_showSeparator)
    {
        painter->setPen(Qt::white);
    }
    else
    {
        painter->setPen(color);
    }
    painter->drawPie(rect, startAngle * 16, spanAngle * 16);
}

void Pie::updateOverlayer()
{
    if (m_showCenterColor)
    {
        setOverlayer(QPixmap(":/images/pie_overlayer_center.png"));
    }
    else
    {
        setOverlayer(QPixmap(":/images/pie_overlayer.png"));
    }
}
