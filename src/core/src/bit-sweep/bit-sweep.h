#pragma once

#include "bit-sweep-allocator.h"
#include "bit-sweep-internal.h"
#include "bit-sweep-printer.h"

unsigned bitSweepWidth(const BitSweep* bitSweep);

unsigned bitSweepHeight(const BitSweep* bitSweep);

unsigned bitSweepBombCount(const BitSweep* bitSweep);

int bitSweepOpenedCellsCount(const BitSweep* bitSweep);

int bitSweepNonBombCellsCount(const BitSweep* bitSweep);

bool bitSweepIsFinished(const BitSweep* bitSweep);

Cell*** bitSweepCells(const BitSweep* bitSweep);

Cell* openCellAt(BitSweep* bitSweep, const int i, const int j);