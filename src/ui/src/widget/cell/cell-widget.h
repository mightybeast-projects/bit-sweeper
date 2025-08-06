#include "bit-sweep.h"
#include "raylib.h"

typedef struct CellWidget
{
    Rectangle rect;
    Cell* cell;
    bool isClicked;
} CellWidget;

CellWidget* allocateCellWidget(Rectangle rect);

void handleCellWidgetInput(CellWidget* widget);

void drawCellWidget(const CellWidget* widget);

void freeCellWidget(CellWidget* widget);