#include "circle.h"
#include <QPainter>

Circle::Circle(QWidget *parent) : QWidget(parent)
{
    this->setBackgroundRole(QPalette::Shadow);

}

void Circle::paintEvent(QPaintEvent *p)
{
    QPainter painter(this);
    QPen pen;                                 //创建一个画笔
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.setBrush(QBrush(QColor(Qt::green)));

    int x = this->width();
    int y = this->height();
//    painter.drawEllipse(0, 0, x,  y);

    const static QPointF points[3] = {
        QPointF(x/2, 0),
        QPointF(0, y),
        QPointF(x, y)
    };

    painter.drawConvexPolygon(points, 3); // 绘制多边形
}
