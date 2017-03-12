#include "IShape.h"

bool IShape::moveDown(Block_t **blocks)
{
    if (m_ypos == m_height)
    {
        return false;
    }
    int ypos = m_ypos;
    m_ypos++;
    if (!checkCrash(blocks))
    {
        m_ypos = ypos;
        return false;
    }
    return true;
}

void IShape::moveLeft(Block_t **blocks) {
    int xpos = m_xpos;
    m_xpos--;
    if (!checkCrash(blocks))
    {
        m_xpos = xpos;
    }
}

void IShape::moveRight(Block_t **blocks)
{
    int xpos = m_xpos;
    m_xpos++;
    if (!checkCrash(blocks))
    {
        m_xpos = xpos;
    }
}

void IShape::rotateLeft(Block_t **blocks)
{
    int angel = m_angle;
    m_angle++;
    if (!checkCrash(blocks))
    {
        m_angle = angel;
    }
}

void IShape::rotateRight(Block_t **blocks)
{
    int angel = m_angle;
    m_angle--;
    if (!checkCrash(blocks))
    {
        m_angle = angel;
    }
}

bool IShape::checkCrash(Block_t **blocks) {
    QVector<PosBlock_t> bs = getBlocks();
    for (int i=0; i<bs.size(); i++)
    {		
		PosBlock_t& b = bs[i];
        if ( b.x < 0 || b.x >= m_width            // 横坐标越界
             || b.y < 0 || b.y >= m_height        // 纵坐标越界
             || (NULL != blocks
                 && blocks[b.y][b.x].isSolid())) // 与已有的方块碰撞
        {
            return false;
        }
    }
    return true;
}
