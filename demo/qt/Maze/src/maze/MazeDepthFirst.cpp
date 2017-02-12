#include "MazeDepthFirst.h"
#include "Util.h"

#include <QDebug>

MazeDepthFirst::MazeDepthFirst()
    : IMaze()
{

}

void MazeDepthFirst::make(int x, int y)
{
    m_x = x;
    m_y = y;
    initCellAndWall(x, y);

    m_cellStack.clear();
    m_curCell = MazeCell_t(0,0); //设置入口
    startWalk();

    QMapIterator<quint64, MazeWall_t> it(m_walls);
    while (it.hasNext())
    {
        it.next();
        MazeWall_t w = it.value();
        if (w.exist)
        {
            m_resultWalls.push_back(QLine(w.x1, w.y1, w.x2, w.y2));
        }
    }
}

QVector<QLine> MazeDepthFirst::getWalls()
{
    return m_resultWalls;
}

QVector<QPoint> MazeDepthFirst::getResult()
{
    return m_result;
}

void MazeDepthFirst::initCellAndWall(int x, int y)
{
    m_resultWalls.clear();
    m_cells.clear();
    m_walls.clear();
    m_result.clear();

    for (int i=0; i<x; i++)
    {
        for (int j=0; j<y; j++)
        {
            MazeCell_t cell(i,j);
            m_cells[cell.value()] = cell;

            MazeWall_t wall1(i,j,i+1,j);
            MazeWall_t wall2(i,j,i,j+1);

            m_walls[wall1.value()] = wall1;
            m_walls[wall2.value()] = wall2;

            if (i == x-1)
            {
                MazeWall_t wall(x,j,x,j+1);
                m_walls[wall.value()] = wall;
            }
        }

        MazeWall_t wall(i,y,i+1,y);
        m_walls[wall.value()] = wall;
    }

    // 入口和出口
    MazeWall_t wallIn(0,0,0,1);
    MazeWall_t wallOut(x,y-1,x,y);
    m_walls[wallIn.value()].exist = false;
    m_walls[wallOut.value()].exist = false;
}

void MazeDepthFirst::startWalk()
{
    while (!walk()){ } // 防止因为递归调用层级太多，造成栈溢出
}

bool MazeDepthFirst::walk()
{
    m_cells[m_curCell.value()].checked = true;

    // 出口位置，记录其路径
    if (m_curCell.x == m_x - 1 && m_curCell.y == m_y -1 && m_result.isEmpty())
    {
        m_result.push_back(QPoint(m_curCell.x, m_curCell.y));
        QStack<MazeCell_t> c = m_cellStack;
        while (!c.isEmpty())
        {
            m_result.push_back(QPoint(c.top().x, c.top().y));
            c.top();
            c.pop();
        }
    }

    QVector<MazeCell_t> neighbors;
    getUncheckedNeighbors(neighbors);
    if (neighbors.size() == 0)
    {
        if (m_cellStack.isEmpty())
        {
            return true;
        }

        m_curCell = m_cellStack.top();
        m_cellStack.pop();
    }
    else
    {
        int index = Util::random(neighbors.size()-1);
        m_cellStack.push(m_curCell);

        removeWall(m_curCell, neighbors[index]);
        m_curCell = neighbors[index];
    }

    return false;
}

void MazeDepthFirst::getUncheckedNeighbors(QVector<MazeCell_t> &neighbors)
{
    neighbors.clear();

    // 一个cell最多只有4个邻居
    MazeCell_t up(m_curCell.x, m_curCell.y-1);
    MazeCell_t down(m_curCell.x, m_curCell.y+1);
    MazeCell_t left(m_curCell.x-1, m_curCell.y);
    MazeCell_t right(m_curCell.x+1, m_curCell.y);

    if (m_cells.contains(up.value()) && !m_cells[up.value()].checked)
    {
        neighbors.push_back(up);
    }
    if (m_cells.contains(down.value()) && !m_cells[down.value()].checked)
    {
        neighbors.push_back(down);
    }
    if (m_cells.contains(left.value()) && !m_cells[left.value()].checked)
    {
        neighbors.push_back(left);
    }
    if (m_cells.contains(right.value()) && !m_cells[right.value()].checked)
    {
        neighbors.push_back(right);
    }
}

void MazeDepthFirst::removeWall(const MazeCell_t &c1, const MazeCell_t &c2)
{
    MazeWall_t w;
    if (c1.x == c2.x)
    {
        if (c1.y < c2.y)
        {
            w = MazeWall_t(c2.x, c2.y, c2.x+1, c2.y);
        }
        else
        {
            w = MazeWall_t(c1.x, c1.y, c1.x+1, c1.y);
        }
    }
    else
    {
        if (c1.x < c2.x)
        {
            w = MazeWall_t(c2.x, c2.y, c2.x, c2.y+1);
        }
        else
        {
            w = MazeWall_t(c1.x, c1.y, c1.x, c1.y+1);
        }
    }

    m_walls[w.value()].exist = false;
}
