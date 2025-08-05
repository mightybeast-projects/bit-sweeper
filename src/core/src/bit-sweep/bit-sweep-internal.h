#pragma once

#include "cell.h"

typedef struct BitSweep
{
    unsigned width;
    unsigned height;
    unsigned bombCount;
    int openedCellsCount;
    bool isFinished;
    Cell*** cells;
} BitSweep;