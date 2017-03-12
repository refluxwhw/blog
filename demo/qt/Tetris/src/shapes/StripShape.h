#ifndef STRIPSHAPE_H
#define STRIPSHAPE_H

#include "IShape.h"

class StripShape : public IShape
{
public:
    StripShape(int width=0, int height=0, int xpos=0, int ypos=0, unsigned char angle=0);
    virtual QVector<PosBlock_t> getBlocks();
};

#endif // STRIPSHAPE_H
