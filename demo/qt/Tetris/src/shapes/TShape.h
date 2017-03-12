#ifndef TSHAPE_H
#define TSHAPE_H

#include "IShape.h"

class TShape : public IShape
{
public:
    TShape(int width=0, int height=0, int xpos=0, int ypos=0, unsigned char angle=0);
    virtual QVector<PosBlock_t> getBlocks();
};

#endif // TSHAPE_H
