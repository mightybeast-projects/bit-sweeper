#pragma once

#include "bit-sweep-internal.h"

typedef struct BitSweepParams
{
    unsigned seed;
    unsigned rows;
    unsigned cols;
    unsigned bombCount;
} BitSweepParams;

BitSweep* allocateBitSweep(BitSweepParams params);

void freeBitSweep(BitSweep* bitSweep);