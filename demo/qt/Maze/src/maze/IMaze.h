#ifndef IMAZE_H
#define IMAZE_H

#include <QVector>
#include <QLine>

class IMaze
{
public:
    IMaze(){}
    virtual void make(int x, int y) = 0;
    virtual QVector<QLine> getWalls() = 0;
    virtual QVector<QPoint> getResult() = 0;
};

#endif // IMAZE_H
