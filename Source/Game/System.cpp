#include <stdlib.h>
#include "Game/System.h"

u32 gKey = 0, gKeyTrg = 0;

int Random(int min, int max)
{
    const int range = max - min + 1;
    return (rand() % range) + min;
}
