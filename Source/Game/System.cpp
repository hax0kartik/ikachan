#include <stdlib.h>
#include "Game/System.h"

int Random(int min, int max)
{
    const int range = max - min + 1;
    return (rand() % range) + min;
}
