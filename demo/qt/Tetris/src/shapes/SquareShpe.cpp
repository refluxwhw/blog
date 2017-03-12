#include "SquareShpe.h"

SquareShpe::SquareShpe(int width, int height, int xpos, int ypos)
    : IShape(width, height, xpos, ypos)
{
    // check
    m_color = QColor(Qt::darkGray);
}

QVector<PosBlock_t> SquareShpe::getBlocks()
{
    QVector<PosBlock_t> blocks;
    PosBlock_t block1(m_xpos, m_ypos, m_color);
    PosBlock_t block2(m_xpos+1, m_ypos, m_color);
    PosBlock_t block3(m_xpos, m_ypos+1, m_color);
    PosBlock_t block4(m_xpos+1, m_ypos+1, m_color);

    blocks.push_back(block1);
    blocks.push_back(block2);
    blocks.push_back(block3);
    blocks.push_back(block4);

    return blocks;
}
