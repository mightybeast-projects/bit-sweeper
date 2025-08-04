#pragma once

#include "bit-sweep-allocator.h"
#include "bit-sweep-internal.h"
#include "bit-sweep-printer.h"

unsigned int bitSweepWidth(const BitSweep* bitSweep);

unsigned int bitSweepHeight(const BitSweep* bitSweep);

unsigned int bitSweepBombCount(const BitSweep* bitSweep);

bool bitSweepIsFinished(const BitSweep* bitSweep);

Cell*** bitSweepCells(const BitSweep* bitSweep);

Cell* openCellAt(BitSweep* bitSweep, const int i, const int j);