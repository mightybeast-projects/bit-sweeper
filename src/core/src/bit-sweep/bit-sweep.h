#include "cell.h"

typedef struct BitSweep BitSweep;

typedef struct BitSweepParams
{
    unsigned int seed;
    unsigned int rows;
    unsigned int cols;
    unsigned int bombCount;
} BitSweepParams;

BitSweep* allocateBitSweep(BitSweepParams params);

unsigned int bitSweepWidth(const BitSweep* bitSweep);

unsigned int bitSweepHeight(const BitSweep* bitSweep);

unsigned int bitSweepBombCount(const BitSweep* bitSweep);

Cell*** bitSweepCells(const BitSweep* bitSweep);

Cell* openCellAt(BitSweep* bitSweep, const int i, const int j);

void printBitSweep(const BitSweep* bitSweep);

void freeBitSweep(BitSweep* bitSweep);