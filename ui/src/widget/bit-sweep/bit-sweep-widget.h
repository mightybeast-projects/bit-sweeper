#pragma once

#include "bit-sweep.h"
#include "cell-widget.h"

typedef struct BitSweepWidget
{
    CellWidget*** cellsWidgets;
    BitSweep* bitSweep;
} BitSweepWidget;

BitSweepWidget* allocateBitSweepWidget(const BitSweepParams params);
void freeBitSweepWidget(BitSweepWidget* const widget);

void drawBitSweepWidget(const BitSweepWidget* const widget);