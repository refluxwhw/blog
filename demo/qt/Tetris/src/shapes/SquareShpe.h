#ifndef SQUARESHPE_H
#define SQUARESHPE_H

#include "IShape.h"

class SquareShpe : public IShape
{
public:
    SquareShpe(int width=0, int height=0, int xpos=0, int ypos=0);
    virtual void rotateLeft(Block_t **){return;}
    virtual void rotateRight(Block_t **){return;}
    virtual QVector<PosBlock_t> getBlocks();
};

#endif // SQUARESHPE_H
