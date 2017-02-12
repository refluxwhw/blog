#ifndef CIRCLE_H
#define CIRCLE_H

#include <QWidget>

class Circle : public QWidget
{
    Q_OBJECT
public:
    explicit Circle(QWidget *parent = 0);


protected:
    void paintEvent(QPaintEvent* p);

signals:

public slots:

private:
    int size;
};

#endif // CIRCLE_H
