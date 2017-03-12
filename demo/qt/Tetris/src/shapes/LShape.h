#ifndef LSHAPE_H
#define LSHAPE_H

#include "IShape.h"

class LShape : public IShape
{
public:
    LShape(int width=0, int height=0, int xpos=0, int ypos=0, unsigned char angle=0);
    virtual QVector<PosBlock_t> getBlocks();
};

#endif // LSHAPE_H
