#pragma once

#include "cell.h"

typedef struct BitSweep
{
    unsigned int width;
    unsigned int height;
    unsigned int bombCount;
    int openedCellsCount;
    bool isFinished;
    Cell*** cells;
} BitSweep;