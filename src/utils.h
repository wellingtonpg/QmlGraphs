#ifndef UTILS
#define UTILS

#include <QObject>

class LegendAlignment : public QObject
{
    Q_OBJECT
    Q_ENUMS(_LegendAlignment)
public:
    typedef enum {
        Left,
        Bottom,
        Right,
        Top
    } _LegendAlignment;
};

#endif // UTILS

