#include "pie.h"

#define PI 3.14159265

Pie::Pie(QQuickItem *parent):
    QQuickPaintedItem(parent),
    m_model(NULL),
    m_showSeparator(false),
    m_showShadow(false),
    m_showCenterColor(false),
    m_centerColor(255, 255, 255),
    m_selectedSlice(NULL)
{
    updateOverlayer();
    setAcceptHoverEvents(true);

    QObject::connect(this, SIGNAL(antialiasingChanged(bool)), SLOT(updateAntialiasing(bool)));
}

Pie::~Pie()
{
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
        update();
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
        update();
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
        update();
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
        update();
    }
}

Slice *Pie::selectedSlice() const
{
    return m_selectedSlice;
}

void Pie::setSelectedSlice(Slice *slice)
{
    if (slice != m_selectedSlice)
    {
        m_selectedSlice = slice;
        emit selectedSliceChanged();
    }
}

void Pie::paint(QPainter *painter)
{
    Q_ASSERT(painter);
    painter->setRenderHints(QPainter::Antialiasing, true);

    QRectF graphRect = boundingRect();
    QPointF center = graphRect.center();

    qreal currentAngle = 90;
    for (unsigned int i = 0; i < m_model->sliceCount(); ++i)
    {
        Slice *slice = m_model->slice(i);
        qreal spanAngle = -360 * (slice->value() / 100.0);
        paintPiece(painter, graphRect, currentAngle, spanAngle, slice->color());

        // Save center point
        qreal pos = 0.5;
        if (showCenterColor())
        {
            pos = 0.75;
        }
        qreal x = center.x() + (cos((currentAngle + (spanAngle / 2.0)) * PI / 180.0) * (center.x() * pos));
        qreal y = center.y() - (sin((currentAngle + (spanAngle / 2.0)) * PI / 180.0) * (center.y() * pos));
        slice->setCenterPoint(QPointF(x, y));

        QVector<QPointF> points;
        points.push_back(center);
        points.push_back(QPointF(cos(currentAngle * PI / 180.0) * center.x() + center.x(),
                                 -sin(currentAngle * PI / 180.0) * center.y() + center.y()));

        for (qreal i = -1; i > spanAngle; i = i - 5)
        {
            qreal angle = currentAngle + i;
            points.push_back(QPointF(cos(angle * PI / 180.0) * center.x() + center.x(),
                                     -sin(angle * PI / 180.0) * center.y() + center.y()));
        }
        points.push_back(QPointF(cos((currentAngle + spanAngle) * PI / 180.0) * center.x() + center.x(),
                                 -sin((currentAngle + spanAngle) * PI / 180.0) * center.y() + center.y()));
        slice->setPolygon(points);

        currentAngle += spanAngle;
    }

    // Draw shadow
    if (m_showShadow)
    {
        painter->drawPixmap(graphRect.toRect(), m_overlayer);
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
#include <QDebug>

void Pie::hoverMoveEvent(QHoverEvent* event)
{
    QQuickItem::hoverMoveEvent(event);

    QPoint mousePos = event->pos();
    for (unsigned int i = 0; i < m_model->sliceCount(); ++i)
    {
        Slice *slice = m_model->slice(i);
        if (slice->polygon().containsPoint(mousePos, Qt::OddEvenFill))
        {
            setSelectedSlice(slice);
            return;
        }
    }
}

void Pie::updateAntialiasing(bool)
{
    update();
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
        m_overlayer = QPixmap(":/images/pie_overlayer_center.png");
    }
    else
    {
        m_overlayer = QPixmap(":/images/pie_overlayer.png");
    }
}

