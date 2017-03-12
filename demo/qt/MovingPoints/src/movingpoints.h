#ifndef MOVINGPOINTS_H
#define MOVINGPOINTS_H

#include <QWidget>
#include <QVector>

typedef struct MovingPoint_t_{
    double a;
    QPoint p;
}MovingPoint_t;

class MovingPoints : public QWidget
{
    Q_OBJECT
public:
    explicit MovingPoints(QWidget *parent = 0);
    void init();

protected:
    void timerEvent(QTimerEvent*);
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*e);

signals:

public slots:

private:
    void changeColor();

private:
    // 每个点的坐标都是用 0~1024*1024 表示浮点数0~1
    // 在绘图时，重新计算其确切的位置
    QVector<MovingPoint_t> m_points;
    bool m_init;
    QColor m_color;

    int m_r;
    int m_g;
    int m_b;
    int m_rx;
    int m_gx;
    int m_bx;
};

#endif // MOVINGPOINTS_H
