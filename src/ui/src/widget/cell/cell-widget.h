#include "bit-sweep.h"
#include "raylib.h"

typedef struct CellWidget
{
    Rectangle rect;
    Cell* cell;
} CellWidget;

CellWidget* allocateCellWidget(Rectangle rect);

void drawCellWidget(const CellWidget* widget);

void freeCellWidget(CellWidget* widget);