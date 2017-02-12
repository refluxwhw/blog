#ifndef MAZEDEPTHFIRST_H
#define MAZEDEPTHFIRST_H

#include "IMaze.h"
#include <QMap>
#include <QVector>
#include <QStack>
#include <QMapIterator>

typedef struct MazeCell_t_ {
    quint16 x;
    quint16 y;
    bool checked;
    MazeCell_t_() : x(0), y(0), checked(false) {}
    MazeCell_t_(quint16 x, quint16 y,bool c = false)
        : x(x), y(y), checked(c) {}
    bool operator ==(const struct MazeCell_t_& c) {
        return x == c.x && y == c.y;
    }
    quint32 value(){return ((quint32)x << 16) + ((quint32)y << 0);}
} MazeCell_t;

typedef struct MazeWall_t_ {
    quint16 x1;
    quint16 y1;
    quint16 x2;
    quint16 y2;
    bool exist;

    MazeWall_t_() : x1(0), y1(0), x2(0), y2(0), exist(true) {}
    MazeWall_t_(quint16 x1, quint16 y1, quint16 x2,
                quint16 y2, bool exist = true)
        : x1(x1), y1(y1), x2(x2), y2(y2), exist(exist) {}
    MazeWall_t_(quint64 value, bool exist = true)
        : exist(exist) {
        y2 = value & 0xffff;
        value = value >> 16;
        x2 = value & 0xffff;
        value = value >> 16;
        y1 = value & 0xffff;
        value = value >> 16;
        x1 = value & 0xffff;
    }

    quint64 value() {return ((quint64)x1 << 48) + ((quint64)y1 << 32)
                             + ((quint64)x2 << 16) + ((quint64)y2 << 0);}
    bool isExist() {return exist;}

} MazeWall_t;


/**
 * @brief 深度优先算法
 * 选取第一个格子作为起始位置
 *  如果当前格的相邻格存在未标记格时，
 *       随机选择一个作为当前格，并移除两者间的墙，当前格入栈
 *  如果当前格的相邻格不存在未标记的格时
 *       如果栈不为空，
 *           出栈，作为当前格
 *       如果栈为空，
 *           退出
 */
class MazeDepthFirst : public IMaze
{
public:
    MazeDepthFirst();
    ~MazeDepthFirst();
    void make(int x, int y);
    virtual QVector<QLine> getWalls();
    virtual QVector<QPoint> getResult();

private:
    void initCellAndWall(int x, int y);
    void startWalk();
    bool walk();
    void getUncheckedNeighbors(QVector<MazeCell_t>& neighbors);
    void removeWall(const MazeCell_t& c1, const MazeCell_t& c2);

private:
    int m_x;
    int m_y;
    QMap<quint32, MazeCell_t> m_cells;
    QMap<quint64, MazeWall_t> m_walls;
    QVector<QLine> m_resultWalls;

    MazeCell_t m_curCell;
    QStack<MazeCell_t> m_cellStack;
    QVector<QPoint> m_result;
};

#endif // MAZEDEPTHFIRST_H
