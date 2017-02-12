#include "MazeRecursionDivision.h"
#include <QRect>
#include "Util.h"

MazeRecursionDivision::MazeRecursionDivision()
    : IMaze()
{

}

void MazeRecursionDivision::make(int x, int y)
{
    m_walls.clear();
    makeBorder(x,y);
    divisionRect(QPoint(0,0), QPoint(x,y));
}

void MazeRecursionDivision::makeBorder(int x, int y)
{
    m_walls.push_back(QLine(0, 0, x, 0));
    m_walls.push_back(QLine(0, y, x, y));
    m_walls.push_back(QLine(0, 1, 0, y));
    m_walls.push_back(QLine(x, 0, x, y - 1));
}

void MazeRecursionDivision::makeLine(QPoint p1, QPoint p2)
{
    QRect rect(p1, p2);

    int width = p2.x() - p1.x();
    int height = p2.y() - p1.y();

    int dx = 0 == width ? 0 : Util::random(width - 1);
    int dy = 0 == height ? 0 : Util::random(height - 1);

    QPoint d1 = rect.topLeft() + QPoint(dx, dy);
    QPoint d2 = d1 + (width == 0 ? QPoint(0,1) : QPoint(1,0));

    m_walls.push_back(QLine(p1, d1));
    m_walls.push_back(QLine(p2, d2));

    //qDebug() << QString("dx = %1; dy = %2").arg(dx).arg(dy);
}

void MazeRecursionDivision::divisionRect(const QPoint &topLeft, const QPoint &bottomRight)
{
    int width = bottomRight.x() - topLeft.x();
    int height = bottomRight.y() - topLeft.y();
    if (width == 1 || height == 1)
    {
        return;
    }

    int direction = Util::random(1);
    int d;
    QPoint p1, p2;
    if (0 == direction) // 0-横线
    {
        d = Util::random(height - 2) + 1;
        p1 = QPoint(topLeft.x(), topLeft.y() + d);
        p2 = QPoint(bottomRight.x(), topLeft.y() + d);
    }
    else // 1-竖线
    {
        d = Util::random(width - 2) + 1;
        p1 = QPoint(topLeft.x() + d, topLeft.y());
        p2 = QPoint(topLeft.x() + d, bottomRight.y());
    }

    makeLine(p1, p2);

    divisionRect(topLeft, p2);
    divisionRect(p1, bottomRight);
}
