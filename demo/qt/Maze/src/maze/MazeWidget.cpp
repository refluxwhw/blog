#include "MazeWidget.h"
#include <QPainter>
#include <QDateTime>
#include <stdlib.h>
#include <math.h>
#include <QThread>
#include <QDebug>
#include "MazeRecursionDivision.h"
#include "MazeDepthFirst.h"

MazeWidget::MazeWidget(QWidget *parent, int x, int y) :
    QWidget(parent)
{
    m_maze = new MazeDepthFirst();
    this->reUpdate(x, y);
}

MazeWidget::~MazeWidget()
{
    delete m_maze;
}

void MazeWidget::reUpdate(int x, int y)
{
    m_maze->make(x, y);
    m_lines = m_maze->getWalls();
    m_result.clear();
    update();
}

void MazeWidget::reslove()
{
    m_result = m_maze->getResult();
    update();
}

void MazeWidget::paintEvent(QPaintEvent *p)
{
    Q_UNUSED(p);

    QPainter painter(this);
    QPen pen;//创建一个画笔
    pen.setColor(Qt::darkCyan);
    pen.setWidth(1);
    painter.setPen(pen);

    for(int i = 0;i<m_lines.size();i++)
    {
        painter.drawLine(m_lines[i].p1() * 10, m_lines[i].p2() * 10);
    }

    pen.setColor(Qt::red);
    painter.setPen(pen);
    for (int i=0; i<m_result.size()-1; i++)
    {
        painter.drawLine(m_result[i].x() * 10 + 5, m_result[i].y() * 10 + 5,
                         m_result[i+1].x() * 10 + 5, m_result[i+1].y() * 10 + 5);
    }
}

