#pragma once

#include "bit-sweep-internal.h"

typedef struct BitSweepParams
{
    unsigned seed;
    unsigned cols;
    unsigned rows;
    unsigned bombCount;
} BitSweepParams;

BitSweep* allocateBitSweep(BitSweepParams params);

void freeBitSweep(BitSweep* bitSweep);