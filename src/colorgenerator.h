#ifndef COLORGENERATOR
#define COLORGENERATOR

#include <QColor>
#include <QVector>

class ColorGenerator
{
public:
    static ColorGenerator& instance()
    {
        static ColorGenerator cg;
        return cg;
    }

    QColor getColor()
    {
        int p = m_p++ % m_colors.size();
        return m_colors[p];
    }
private:
    ColorGenerator() :
        m_p(int())
    {
        m_colors.append(QColor(91, 144, 191));
        m_colors.append(QColor(150, 181, 180));
        m_colors.append(QColor(163, 190, 140));
        m_colors.append(QColor(171, 121, 103));
        m_colors.append(QColor(208, 135, 112));
        m_colors.append(QColor(180, 142, 173));
        m_colors.append(QColor(124, 181, 236));
        m_colors.append(QColor(247, 163, 92));
        m_colors.append(QColor(144, 237, 125));
        m_colors.append(QColor(67, 67, 72));
        m_colors.append(QColor(253, 180, 92));
        m_colors.append(QColor(70, 191, 189));
        m_colors.append(QColor(247, 70, 74));
    }
    ColorGenerator(ColorGenerator const&) = delete;
    void operator=(ColorGenerator const&) = delete;

    int m_p;
    QVector<QColor> m_colors;
};

#endif // COLORGENERATOR

