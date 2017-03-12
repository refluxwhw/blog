#ifndef ZOPPSHAPE_H
#define ZOPPSHAPE_H

#include "IShape.h"

class ZOppShape : public IShape
{
public:
    ZOppShape(int width=0, int height=0, int xpos=0, int ypos=0, unsigned char angle=0);
    virtual QVector<PosBlock_t> getBlocks();
};

#endif // ZOPPSHAPE_H
