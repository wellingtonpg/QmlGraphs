#include "slice.h"
#include "src/colorgenerator.h"

Slice::Slice(QObject *parent) :
    QObject(parent),
    m_color(ColorGenerator::instance().getColor())
{
}

QString Slice::label() const
{
    return m_label;
}

void Slice::setLabel(const QString &label)
{
    if (label != m_label)
    {
        m_label = label;
        labelChanged();
    }
}

qreal Slice::value() const
{
    return m_value;
}

void Slice::setValue(const qreal &value)
{
    if (value != m_value)
    {
        m_value = value;
        emit valueChanged();
    }
}

QColor Slice::color() const
{
    return m_color;
}

QPointF Slice::centerPoint() const
{
    return m_centerPoint;
}

void Slice::setCenterPoint(const QPointF &centerPoint)
{
    if (centerPoint != m_centerPoint)
    {
        m_centerPoint = centerPoint;
        emit centerPointChanged();
    }
}

QPolygonF Slice::polygon() const
{
    return m_polygon;
}

void Slice::setPolygon(const QPolygonF &polygon)
{
    if (polygon != m_polygon)
    {
        m_polygon = polygon;
    }
}

void Slice::setColor(const QColor &color)
{
    if (color != m_color)
    {
        m_color = color;
        emit colorChanged();
    }
}
