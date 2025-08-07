#pragma once

#include "bit-sweep-allocator.h"
#include "bit-sweep-printer.h"
#include "cell.h"

unsigned bitSweepWidth(const BitSweep* const bitSweep);
unsigned bitSweepHeight(const BitSweep* const bitSweep);
unsigned bitSweepBombCount(const BitSweep* const bitSweep);
int bitSweepOpenedCellsCount(const BitSweep* const bitSweep);
int bitSweepNonBombCellsCount(const BitSweep* const bitSweep);
bool bitSweepIsFinished(const BitSweep* const bitSweep);

Cell*** bitSweepCells(const BitSweep* const bitSweep);

Cell* openCellAt(BitSweep* const bitSweep, const int i, const int j);

Cell* toggleCellMarkAt(BitSweep* const bitSweep, const int i, const int j);