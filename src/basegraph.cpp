#include "basegraph.h"

BaseGraph::BaseGraph(QQuickPaintedItem *parent) :
    QQuickPaintedItem(parent)
{
    QQuickItem::setAntialiasing(true);
    QObject::connect(this, SIGNAL(QQuickItem::antialiasingChanged()), SLOT(QQuickItem::update()));
}

QString BaseGraph::title() const
{
    return m_title;
}

void BaseGraph::setTitle(const QString &title)
{
    if (title != m_title)
    {
        m_title = title;
        emit titleChanged();
    }
}

QString BaseGraph::subtitle() const
{
    return m_subtitle;
}

void BaseGraph::setSubtitle(const QString &subtitle)
{
    if (subtitle != m_subtitle)
    {
        m_subtitle = subtitle;
        emit subtitleChanged();
    }
}

void BaseGraph::paint(QPainter *painter)
{
    Q_ASSERT(painter);

    qDebug() << "BaseGraph::paint antialiasing = " << antialiasing();
    //painter->setRenderHints(QPainter::Antialiasing, antialiasing());
    painter->setRenderHint(QPainter::Antialiasing);

    if (!title().isEmpty())
    {
        painter->setFont(QFont("Helvetica", 20));
        painter->setPen(QColor(0, 0, 0));
        painter->drawText(QQuickItem::boundingRect(), Qt::AlignTop | Qt::AlignHCenter, title());
    }
    if (!subtitle().isEmpty())
    {
        painter->setFont(QFont("Helvetica", 12));
        QRectF rect = QQuickItem::boundingRect();
        rect.adjust(0, 30, 0, 0);
        painter->drawText(rect, Qt::AlignTop | Qt::AlignHCenter, subtitle());
    }
}

QPixmap BaseGraph::overlayer() const
{
    return m_overlayer;
}

void BaseGraph::setOverlayer(const QPixmap &overlayer)
{
    m_overlayer = overlayer;
}

QRectF BaseGraph::boundingRect() const
{
    QRectF rect = QQuickItem::boundingRect();
    rect.adjust(0, 60, 0, 0);
    return rect;
}
