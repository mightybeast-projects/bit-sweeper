#pragma once

#include "cell.h"
#include "mersenne-twister.h"

typedef struct BitSweep
{
    unsigned width;
    unsigned height;
    unsigned bombCount;
    int openedCellsCount;
    bool isFinished;
    MTState* randomState;
    Cell*** cells;
} BitSweep;