#include "slice.h"

Slice::Slice(QObject *parent) :
    QObject(parent),
    m_color(0, 0, 0)
{
}

QString Slice::label() const
{
    return m_label;
}

void Slice::setLabel(QString label)
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

void Slice::setValue(qreal value)
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

void Slice::setColor(QColor color)
{
    if (color != m_color)
    {
        m_color = color;
        emit colorChanged();
    }
}
