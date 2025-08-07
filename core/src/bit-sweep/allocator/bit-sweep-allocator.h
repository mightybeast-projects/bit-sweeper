#pragma once

typedef struct BitSweep BitSweep;

typedef struct BitSweepParams
{
    unsigned seed;
    unsigned cols;
    unsigned rows;
    unsigned bombCount;
} BitSweepParams;

BitSweep* allocateBitSweep(const BitSweepParams params);
void freeBitSweep(BitSweep* const bitSweep);