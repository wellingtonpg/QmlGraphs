#ifndef SLICE_H
#define SLICE_H

#include <QObject>
#include <QColor>

class Slice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    explicit Slice(QObject *parent = 0);

    QString label() const;
    void setLabel(QString label);

    qreal value() const;
    void setValue(qreal value);

    QColor color() const;
    void setColor(QColor color);

signals:
    void labelChanged();
    void valueChanged();
    void colorChanged();

private:
    QString m_label;
    qreal m_value;
    QColor m_color;
};

#endif // SLICE_H
