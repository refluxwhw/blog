#include "mypainterwidget.h"
#include <QString>
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QPushButton>



MyPainterWidget::MyPainterWidget(QWidget* parent)
    :QWidget(parent)
{
    setMinimumSize(240,120);
    setMaximumSize(480,240);
    this->setMouseTracking(true);
    this->isPressed = false;

    c = new Circle(this);
    //c->setGeometry(0, 0, 50, 50);
    c->hide();
}

MyPainterWidget::~MyPainterWidget()
{

}

void MyPainterWidget::paintEvent(QPaintEvent*p) 
{
    QPainter painter(this);
    QPen pen;                                 //创建一个画笔
    pen.setColor(Qt::darkCyan);
    pen.setWidth(5);
    painter.setPen(pen);

    for(int i = 0;i<lines.size();i++)
    {
        myLine* pLine = lines[i];
        painter.drawLine(pLine->startPnt,pLine->endPnt);
    }
}

void MyPainterWidget::mousePressEvent(QMouseEvent *e)
{
    setCursor(Qt::PointingHandCursor);
    startPnt = e->pos();
    endPnt = e->pos();
    this->isPressed = true;

    QPoint p = e->pos();
    c->setGeometry(p.x() - 10, p.y() - 10, 20, 20);
    c->show();
    //QString msg ="("+QString::number(e->x())+","+QString::number(e->y())+")";
    //QMessageBox::warning(this,tr("Warning"),msg,QMessageBox::Ok);
}

void MyPainterWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(this->isPressed)
    {
        endPnt = e->pos();

        myLine* line = new myLine;  //put the new line into vector
        line->startPnt = startPnt;
        line->endPnt = endPnt;
        this->lines.push_back(line);

        update();                  //repainter，call paintEvent
        startPnt = endPnt;

        c->setGeometry(endPnt.x() - 10, endPnt.y() - 10, 20, 20);
    }
}

void MyPainterWidget::mouseReleaseEvent(QMouseEvent *e)
{
    setCursor(Qt::ArrowCursor);
    this->isPressed = false;
    c->hide();
}
