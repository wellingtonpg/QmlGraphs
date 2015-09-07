#ifndef PIE_H
#define PIE_H

#include <QQuickPaintedItem>
#include <QPainter>

#include "piemodel.h"

class Pie : public QQuickPaintedItem
{
    Q_OBJECT
    Q_DISABLE_COPY(Pie)
    //Q_CLASSINFO("DefaultProperty", "model")
    Q_PROPERTY(PieModel *model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(bool showSeparator READ showSeparator WRITE setShowSeparator NOTIFY showSeparatorChanged)
    Q_PROPERTY(bool showShadow READ showShadow WRITE setShowShadow NOTIFY showShadowChanged)
    Q_PROPERTY(bool showCenterColor READ showCenterColor WRITE setShowCenterColor NOTIFY showCenterColorChanged)
    Q_PROPERTY(QColor centerColor READ centerColor WRITE setCenterColor NOTIFY centerColorChanged)
    Q_PROPERTY(Slice *selectedSlice READ selectedSlice NOTIFY selectedSliceChanged)

public:
    explicit Pie(QQuickItem *parent = 0);
    ~Pie();

    PieModel* model() const;
    void setModel(PieModel *model);

    bool showSeparator() const;
    void setShowSeparator(bool showSeparator);

    bool showShadow() const;
    void setShowShadow(bool showShadow);

    bool showCenterColor() const;
    void setShowCenterColor(bool showCenterColor);

    QColor centerColor() const;
    void setCenterColor(QColor centerColor);

    Slice* selectedSlice() const;
    void setSelectedSlice(Slice *slice);

protected:
    void paint(QPainter *painter);
    void hoverMoveEvent(QHoverEvent* event);

signals:
    void modelChanged();
    void showSeparatorChanged();
    void showShadowChanged();
    void centerColorChanged();
    void showCenterColorChanged();
    void selectedSliceChanged();

private slots:
    void updateAntialiasing(bool);

private:
    void paintPiece(QPainter * painter, const QRectF &rect, qreal startAngle, qreal endAngle, const QColor &color);
    void updateOverlayer();

    PieModel *m_model;
    bool m_showSeparator;
    bool m_showShadow;
    bool m_showCenterColor;
    QColor m_centerColor;
    QPixmap m_overlayer;
    Slice *m_selectedSlice;
};

#endif // PIE_H

