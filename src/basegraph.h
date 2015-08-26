#ifndef GRAPHBASE_H
#define GRAPHBASE_H

#include <QQuickPaintedItem>
#include <QPainter>

class BaseGraph : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString subtitle READ subtitle WRITE setSubtitle NOTIFY subtitleChanged)

public:
    explicit BaseGraph(QQuickPaintedItem *parent = 0);

    QString title() const;
    void setTitle(const QString &title);

    QString subtitle() const;
    void setSubtitle(const QString &subtitle);

protected:
    virtual void paint(QPainter *);

    QPixmap overlayer() const;
    void setOverlayer(const QPixmap &overlayer);

    QRectF boundingRect() const;

signals:
    void titleChanged();
    void subtitleChanged();

private:
    QPixmap m_overlayer;
    QString m_title;
    QString m_subtitle;
};

#endif // GRAPHBASE_H
