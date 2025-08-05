#include "cell-widget.h"
#include "safe-memory.h"
#include "stdio.h"

const Color colors[8] = { SKYBLUE, GREEN, RED, PURPLE, ORANGE, PINK, YELLOW, GRAY };

CellWidget* allocateCellWidget(Rectangle rect)
{
    CellWidget* widget = safeMalloc(sizeof(struct CellWidget));

    widget->rect = rect;
    widget->cell = allocateCell();

    return widget;
}

void drawCellWidget(const CellWidget* widget)
{
    Rectangle rect = widget->rect;

    Color cellColor;

    if (cellIsOpened(widget->cell))
        cellColor = (Color) { 60, 60, 60, 255 };
    else
        cellColor = (Color) { 75, 75, 75, 255 };

    DrawRectangleRounded(rect, 0.1, 10, cellColor);

    if (!cellIsOpened(widget->cell) || cellValue(widget->cell) == ZERO)
        return;

    int x = rect.x + rect.width / 2.75;
    int y = rect.y + rect.width / 5;
    int fontSize = rect.width / 1.5;

    char str[2];

    sprintf(str, "%d", cellValue(widget->cell));

    DrawText(str, x, y, fontSize, colors[cellValue(widget->cell) - 1]);
}

void freeCellWidget(CellWidget* widget)
{
    freeCell(widget->cell);
    free(widget);
}
