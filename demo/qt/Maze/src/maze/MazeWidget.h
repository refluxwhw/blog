#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include <QWidget>
#include <QVector>
#include <QLine>
#include "IMaze.h"

class MazeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MazeWidget( QWidget *parent = 0, int x = 10, int y = 10);
    ~MazeWidget();

    void reUpdate(int x, int y);
    void reslove();

protected:
    void paintEvent(QPaintEvent *p);

private:
    void makeLine(QPoint p1, QPoint p2);
    void divisionRect(const QPoint& topLeft, const QPoint& bottomRight);

private:
    QVector<QLine> m_lines;
    QVector<QPoint> m_result;
    IMaze *m_maze;
};

#endif // MAZEWIDGET_H
