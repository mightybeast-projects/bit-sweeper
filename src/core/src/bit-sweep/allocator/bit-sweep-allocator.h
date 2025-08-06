#pragma once

typedef struct BitSweep BitSweep;

typedef struct BitSweepParams
{
    unsigned seed;
    unsigned cols;
    unsigned rows;
    unsigned bombCount;
} BitSweepParams;

BitSweep* allocateBitSweep(BitSweepParams params);

void freeBitSweep(BitSweep* bitSweep);