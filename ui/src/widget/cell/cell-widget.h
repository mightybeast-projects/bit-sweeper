#pragma once

#include "bit-sweep.h"
#include "raylib.h"

typedef struct CellWidget
{
    bool isClicked;
    Rectangle rect;
    Cell* cell;
    BitSweep* bitSweep;
} CellWidget;

CellWidget* allocateCellWidget(
    const Rectangle rect,
    Cell* const cell,
    BitSweep* const bitSweep);

void freeCellWidget(CellWidget* widget);

void handleCellWidgetInput(CellWidget* widget);

void drawCellWidget(const CellWidget* widget);
