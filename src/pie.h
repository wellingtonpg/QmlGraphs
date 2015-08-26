#ifndef PIE_H
#define PIE_H

#include "basegraph.h"
#include "piemodel.h"

class Pie : public BaseGraph
{
    Q_OBJECT

    Q_CLASSINFO("DefaultProperty", "model")
    Q_PROPERTY(PieModel *model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(bool showSeparator READ showSeparator WRITE setShowSeparator NOTIFY showSeparatorChanged)
    Q_PROPERTY(bool showShadow READ showShadow WRITE setShowShadow NOTIFY showShadowChanged)
    Q_PROPERTY(bool showCenterColor READ showCenterColor WRITE setShowCenterColor NOTIFY showCenterColorChanged)
    Q_PROPERTY(QColor centerColor READ centerColor WRITE setCenterColor NOTIFY centerColorChanged)

public:
    explicit Pie(QQuickPaintedItem *parent = 0);
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

protected:
    void paint(QPainter *painter);

signals:
    void modelChanged();
    void showSeparatorChanged();
    void showShadowChanged();
    void centerColorChanged();
    void showCenterColorChanged();

private:
    void paintPiece(QPainter * painter, const QRectF &rect, qreal startAngle, qreal endAngle, const QColor &color);
    void updateOverlayer();

    PieModel *m_model;
    bool m_showSeparator;
    bool m_showShadow;
    bool m_showCenterColor;
    QColor m_centerColor;
};

#endif // PIE_H
