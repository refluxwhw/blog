#include "Util.h"
#include <stdlib.h>
#include <QDateTime>

Util::Util()
{

}

int Util::random(int x)
{
    // 获取 0~x 的随机数
    static int seed = (int)QDateTime::currentMSecsSinceEpoch();
    srand(seed);
    int r = rand();
    seed += r + (int)QDateTime::currentMSecsSinceEpoch();
    return (r % (x + 1));
}
