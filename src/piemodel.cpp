#include "piemodel.h"

PieModel::PieModel(QObject *parent) :
    QObject(parent)
{
}

QQmlListProperty<Slice> PieModel::slices()
{
    return QQmlListProperty<Slice>(this, m_slices);
    //return QQmlListProperty<Slice>(this, 0, &appendSlice, 0, 0, 0);
}

unsigned int PieModel::sliceCount() const
{
    return m_slices.count();
}

Slice* PieModel::slice(int index) const
{
    return m_slices.at(index);
}
