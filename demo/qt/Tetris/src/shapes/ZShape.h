﻿#ifndef ZSHAPE_H
#define ZSHAPE_H

#include "IShape.h"

class ZShape : public IShape
{
public:
    ZShape(int width=0, int height=0, int xpos=0, int ypos=0, unsigned char angle=0);
    virtual QVector<PosBlock_t> getBlocks();
};

#endif // ZSHAPE_H
