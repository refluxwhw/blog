#include "movingpoints.h"
#include "time.h"
#include "stdlib.h"
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QResizeEvent>

MovingPoints::MovingPoints(QWidget *parent) : QWidget(parent)
{
    m_init = false;
}

#define PI 3.141592654

void MovingPoints::init()
{
    // create points
    if (m_init)
    {
        return;
    }

    srand(time(NULL));
    int w = this->width();
    int h = this->height();
    for (int i=0; i<100; i++)
    {
        MovingPoint_t p;
        p.p = QPoint(rand() % w, rand() % h);
        p.a = rand() % 360 / 180.0 * PI;
        m_points.push_back(p);
    }

    m_init = true;
    m_color = QColor();

    m_r  = 0;
    m_g  = 0;
    m_b  = 0;
    m_rx = 1;
    m_gx = 2;
    m_bx = 3;

    this->startTimer(100);
}


void MovingPoints::timerEvent(QTimerEvent *)
{
    int w = this->width();
    int h = this->height();

    int min = w <= h ? w : h;
    min = min / 100;
    min = min<5 ? 5 : min;

    for (int i=0; i<m_points.size(); i++)
    {
        MovingPoint_t& p = m_points[i];
        QPoint &point = p.p;
        point.setX(point.x() + (int)(cos(p.a) * min));

        if (point.x() < 0)
        {
            point.setX(0);
            p.a = PI - p.a;
        }
        else if (point.x() > w)
        {
            point.setX(w);
            p.a = PI - p.a;
        }
        else
        {
            point.setY(point.y() + (int)(sin(p.a) * min));
            if (point.y() < 0)
            {
                point.setY(0);
                p.a = 2 * PI - p.a;
            }
            else if (point.y() > h)
            {
                point.setY(h);
                p.a = 2 * PI - p.a;
            }
            continue;
        }
    }
    update();
}

void MovingPoints::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;

    changeColor();
    m_color.setRed(m_r);
    m_color.setGreen(m_g);
    m_color.setBlue(m_b);

    pen.setWidth(1);
    int w = this->width();
    int h = this->height();
    int min = w <= h ? w : h;
    min = min * min / 25;

    for (int i=0; i<m_points.size()-1; i++)
    {
        QPoint &a = m_points[i].p;
        for (int j=i+1; j<m_points.size(); j++)
        {
            QPoint &b = m_points[j].p;
            int x = a.x() - b.x();
            int y = a.y() - b.y();
            double len = x * x + y * y;

            if (len <= min)
            {
                double f = 1.0 - len / min;
                m_color.setAlphaF(f);
            }
            else
            {
                continue;
            }

            // draw line
            pen.setColor(m_color);
            painter.setPen(pen);
            painter.drawLine(a, b);
        }
    }
}

void MovingPoints::resizeEvent(QResizeEvent *e)
{
    if (!m_init)
    {
        return;
    }

    QSize oldSize = e->oldSize();
    QSize newSize = e->size();
    int w1 = oldSize.width();
    int h1 = oldSize.height();
    int w2 = newSize.width();
    int h2 = newSize.height();

    for (int i=0; i<m_points.size(); i++)
    {
        QPoint p = m_points[i].p;
        m_points[i].p.setX(p.x() * w2 / w1);
        m_points[i].p.setY(p.y() * h2 / h1);
    }
    update();
}

void MovingPoints::changeColor()
{
    m_r  += m_rx;
    if (m_r < 0)
    {
        m_r = 0;
        m_rx = -m_rx;
    }
    else if (m_r > 255)
    {
        m_r = 255;
        m_rx = -m_rx;
    }

    m_g  += m_gx;
    if (m_g < 0)
    {
        m_g = 0;
        m_gx = -m_gx;
    }
    else if (m_g > 255)
    {
        m_g = 255;
        m_gx = -m_gx;
    }

    m_b  += m_bx;
    if (m_b < 0)
    {
        m_b = 0;
        m_bx = -m_bx;
    }
    else if (m_b > 255)
    {
        m_b = 255;
        m_bx = -m_bx;
    }
}
