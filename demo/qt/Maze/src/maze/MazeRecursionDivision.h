#ifndef MAZERECURSIONDIVISION_H
#define MAZERECURSIONDIVISION_H

#include "IMaze.h"

/**
 * @brief 递归分割算法
 *  迷宫区域为一个大的矩形，随机将其分割为两部分，并在墙上开孔，如此递归
 * 到矩形不能长或宽为1(为1时，分割了还需要开孔，等于无需分割)
 */
class MazeRecursionDivision : public IMaze
{
public:
    MazeRecursionDivision();
    void make(int x, int y);
    virtual QVector<QLine> getWalls() {return m_walls;}
    virtual QVector<QPoint> getResult() {return QVector<QPoint>();}
private:
    void makeBorder(int x, int y);
    void makeLine(QPoint p1, QPoint p2);
    void divisionRect(const QPoint &topLeft, const QPoint &bottomRight);

protected:
    QVector<QLine> m_walls;
};

#endif // MAZERECURSIONDIVISION_H
