#pragma once

#include "bit-sweep-internal.h"

typedef struct BitSweepParams
{
    unsigned int seed;
    unsigned int rows;
    unsigned int cols;
    unsigned int bombCount;
} BitSweepParams;

BitSweep* allocateBitSweep(BitSweepParams params);

void freeBitSweep(BitSweep* bitSweep);