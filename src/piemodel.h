#ifndef PIEMODEL_H
#define PIEMODEL_H

#include <QObject>
#include <QList>
#include <QQmlListProperty>
#include "slice.h"

class PieModel : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("DefaultProperty", "slices")
    Q_PROPERTY(QQmlListProperty<Slice> slices READ slices)

public:
    explicit PieModel(QObject *parent = 0);

    QQmlListProperty<Slice> slices();
    unsigned int sliceCount() const;
    Slice* slice(int index) const;

private:
    QList<Slice *> m_slices;
};

#endif // PIEMODEL_H
