#include "piemodel.h"

PieModel::PieModel(QObject *parent) :
    QObject(parent)
{
}

QQmlListProperty<Slice> PieModel::slices()
{
    return QQmlListProperty<Slice>(this, m_slices);
}

unsigned int PieModel::sliceCount() const
{
    return m_slices.count();
}

Slice* PieModel::slice(int index) const
{
    return m_slices.at(index);
}

