#ifndef TETRIS_H
#define TETRIS_H

#include <QWidget>
#include <QVector>
#include <QColor>

#include "IShape.h"

class Tetris : public QWidget
{
    Q_OBJECT
public:
    explicit Tetris(QWidget *parent = 0);
    ~Tetris();

protected:
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent();

signals:
    void sigEraserLine(int);

public slots:
    void onRestart();      // 重新开始
    void onPause();        // 暂停
    void onGoOn();         // 继续
    void onLeftClicked();  // 左移
    void onRightClicked(); // 右移
    void onRotateLeft();   // 逆时针旋转
    void onRotateRight();  // 顺时针旋转
    void onDownPresse();   // 加速下落
    void onDownRelease();  // 停止加速

    void onFall(); // 掉落

    void onEraserLines();
    void onCreateMovingShape();


private:
    int m_height;
    int m_width;
    int m_size;  // 方块大小
    int m_level; // 等级，等级越高，定时器越小
    bool m_isSpeedup;
    Block_t **m_blocks;     // 禁止的方块
    QColor m_background;   // 背景色

    IShape *m_movingShape; // 正在运动的方块

    QList<int> m_eraserLines;
    int m_stage;
};

#endif // TETRIS_H
