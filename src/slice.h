#ifndef SLICE_H
#define SLICE_H

#include <QObject>
#include <QColor>
#include <QPointF>
#include <QPolygonF>

class Slice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QPointF centerPoint READ centerPoint WRITE setCenterPoint NOTIFY centerPointChanged)

public:
    explicit Slice(QObject *parent = 0);

    QString label() const;
    void setLabel(const QString &label);

    qreal value() const;
    void setValue(const qreal &value);

    QColor color() const;
    void setColor(const QColor &color);

    QPointF centerPoint() const;
    void setCenterPoint(const QPointF &centerPoint);

    QPolygonF polygon() const;
    void setPolygon(const QPolygonF &polygon);

signals:
    void labelChanged();
    void valueChanged();
    void colorChanged();
    void centerPointChanged();

private:
    QString m_label;
    qreal m_value;
    QColor m_color;
    QPointF m_centerPoint;
    QPolygonF m_polygon;
};

#endif // SLICE_H
