#pragma once

#include "bit-sweep.h"
#include "cell-widget.h"

typedef struct BitSweepWidget
{
    CellWidget*** cellsWidgets;
    BitSweep* bitSweep;
} BitSweepWidget;

BitSweepWidget* allocateBitSweepWidget(BitSweepParams params);

void drawBitSweepWidget(const BitSweepWidget* widget);

void freeBitSweepWidget(BitSweepWidget* widget);