#include "cell.h"

typedef struct bitSweep BitSweep;

struct bitSweep
{
    int width;
    int height;
    int bombCount;
    Cell*** cells;
};

BitSweep* allocateBitSweep();

void freeBitSweep(BitSweep* bitSweep);