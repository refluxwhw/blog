#ifndef ISHAPE_H
#define ISHAPE_H

#include <QObject>
#include <QColor>
#include <QVector>

typedef struct Color_t_{
private:
    unsigned char v[4];

public:
    Color_t_(int r=0, int g=0, int b=0, bool solid=false) {
        v[0] = (unsigned char)r;
        v[1] = (unsigned char)g;
        v[2] = (unsigned char)b;
        v[3] = (unsigned char)(solid ? 1 : 0);
    }

    bool isSolid(){return v[3] != 0;}

    QColor color() {return QColor((int)v[0], (int)v[1], (int)v[2]);}
    void setColor(const QColor& c) {
        v[0] = (unsigned char)c.red();
        v[1] = (unsigned char)c.green();
        v[2] = (unsigned char)c.blue();
    }
} Block_t;

typedef struct PosBlock_t_ : Block_t{
    int x;
    int y;
    PosBlock_t_(int x = 0, int y = 0, QColor c = QColor())
        : Block_t(c.red(), c.green(), c.blue(), true), x(x), y(y) {}
} PosBlock_t;

/**
 * @brief 继承时需要做两件事
 * 1. 实现getBlocks方法，返回方块数组；
 * 2. 在构造函数中应该检查边界冲突，并修正。
 */
class IShape
{
public:
    /**
     * @brief IShape
     * @param width[int] 窗口宽度，单位为方块
     * @param height[int] 窗口高度，单位为方块
     * @param xpos[int] 当前形状在窗口中的位置x坐标
     * @param ypos[int] 当前形状在窗口中的位置y坐标
     */
    IShape(int width=0, int height=0, int xpos=0, int ypos=0, unsigned char angle=0)
        : m_width(width), m_height(height),
          m_xpos(xpos), m_ypos(ypos), m_angle(angle) {}

    virtual bool moveDown(Block_t **blocks);
    virtual void moveLeft(Block_t **blocks);
    virtual void moveRight(Block_t **blocks);
    virtual void rotateLeft(Block_t **blocks);
    virtual void rotateRight(Block_t **blocks);
    virtual QVector<PosBlock_t> getBlocks() = 0;

protected:
    virtual bool checkCrash(Block_t **blocks);

protected:
    int m_width;
    int m_height;
    int m_xpos;
    int m_ypos;
    unsigned char m_angle; // 0- 1- 2- 3- 取模4
    QColor m_color;
};

#endif // ISHAPE_H
