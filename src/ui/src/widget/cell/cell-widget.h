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

CellWidget* allocateCellWidget(const Rectangle rect, Cell* cell, BitSweep* bitSweep);

void handleCellWidgetInput(CellWidget* widget);

void drawCellWidget(const CellWidget* widget);

void freeCellWidget(CellWidget* widget);