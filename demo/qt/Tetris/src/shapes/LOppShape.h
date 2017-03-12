#ifndef LOPPSHAPE_H
#define LOPPSHAPE_H

#include "IShape.h"

class LOppShape : public IShape
{
public:
    LOppShape(int width=0, int height=0, int xpos=0, int ypos=0, unsigned char angle=0);
    virtual QVector<PosBlock_t> getBlocks();
};

#endif // LOPPSHAPE_H
