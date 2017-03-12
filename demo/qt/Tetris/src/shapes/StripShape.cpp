#include "StripShape.h"

StripShape::StripShape(int width, int height, int xpos, int ypos, unsigned char angle)
    : IShape(width, height, xpos, ypos, angle)
{
    m_color = QColor(Qt::darkCyan);
}

QVector<PosBlock_t> StripShape::getBlocks()
{
    int angle = m_angle % 2;
    if (angle < 0)
    {
        angle = 2 + angle;
    }
    QVector<PosBlock_t> blocks;
    switch (angle)
    {
        case 0:
            blocks.push_back(PosBlock_t(m_xpos, m_ypos, m_color));
            blocks.push_back(PosBlock_t(m_xpos, m_ypos+1, m_color));
            blocks.push_back(PosBlock_t(m_xpos, m_ypos+2, m_color));
            blocks.push_back(PosBlock_t(m_xpos, m_ypos+3, m_color));
            break;
        case 1:
            blocks.push_back(PosBlock_t(m_xpos, m_ypos, m_color));
            blocks.push_back(PosBlock_t(m_xpos+1, m_ypos, m_color));
            blocks.push_back(PosBlock_t(m_xpos+2, m_ypos, m_color));
            blocks.push_back(PosBlock_t(m_xpos+3, m_ypos, m_color));
            break;
        default:
            break;
    }

    return blocks;
}
