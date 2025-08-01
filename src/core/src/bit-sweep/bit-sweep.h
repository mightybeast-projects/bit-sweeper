#include "cell.h"

typedef struct BitSweep BitSweep;

BitSweep* allocateBitSweep(int rows, int cols, int bombCount);

int bitSweepWidth(const BitSweep* bitSweep);

int bitSweepHeight(const BitSweep* bitSweep);

int bitSweepBombCount(const BitSweep* bitSweep);

Cell*** bitSweepCells(const BitSweep* bitSweep);

void printBitSweep(const BitSweep* bitSweep);

void freeBitSweep(BitSweep* bitSweep);