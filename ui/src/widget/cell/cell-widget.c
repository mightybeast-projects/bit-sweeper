#include "cell-widget.h"
#include "safe-memory.h"
#include "stdio.h"

const static Color colors[10] = {
    BLANK, SKYBLUE, GREEN, PINK, PURPLE, ORANGE, BLUE, YELLOW, GRAY, BLACK
};

static void drawCellBackground(const CellWidget* widget, const Cell* cell);

static void drawCellMark(const Rectangle rect, const Cell* cell);

static void drawCellValue(const Rectangle rect, const Cell* cell);

CellWidget* allocateCellWidget(const Rectangle rect, Cell* cell, BitSweep* bitSweep)
{
    CellWidget* widget = safeMalloc(sizeof(struct CellWidget));

    widget->rect = rect;
    widget->cell = cell;
    widget->bitSweep = bitSweep;

    return widget;
}

void handleCellWidgetInput(CellWidget* widget)
{
    const Vector2 mousePos = GetMousePosition();
    const Rectangle rect = widget->rect;

    Cell* cell = widget->cell;

    bool mouseCollides = CheckCollisionPointRec(mousePos, rect);

    widget->isClicked = IsMouseButtonDown(MOUSE_LEFT_BUTTON) && mouseCollides;

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && mouseCollides)
        openCellAt(widget->bitSweep, cellI(cell), cellJ(cell));

    if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON) && mouseCollides)
        toggleCellMarkAt(widget->bitSweep, cellI(cell), cellJ(cell));
}

void drawCellWidget(const CellWidget* widget)
{
    const Rectangle rect = widget->rect;
    const Cell* cell = widget->cell;

    drawCellBackground(widget, cell);

    if (cellIsMarked(cell))
        drawCellMark(rect, cell);

    if (cellIsOpened(cell))
        drawCellValue(rect, cell);
}

void freeCellWidget(CellWidget* widget)
{
    free(widget);
}

static void drawCellBackground(const CellWidget* widget, const Cell* cell)
{
    const bool gameIsFinished = bitSweepIsFinished(widget->bitSweep);

    if (cellIsOpened(cell) && cellContainsBomb(cell))
        DrawRectangleRounded(widget->rect, 0.1, 10, RED);
    else if (cellIsOpened(cell) || (widget->isClicked && !gameIsFinished))
        DrawRectangleRounded(widget->rect, 0.1, 10, (Color) { 60, 60, 60, 255 });
    else if (!cellIsOpened(cell))
        DrawRectangleRounded(widget->rect, 0.1, 10, (Color) { 75, 75, 75, 255 });
}

static void drawCellMark(const Rectangle rect, const Cell* cell)
{
    const float x = rect.x + rect.width / 2.75;
    const float y = rect.y + rect.width / 5;
    const int fontSize = rect.width / 1.4;

    DrawText("!!!", x, y, fontSize, RED);
}

static void drawCellValue(const Rectangle rect, const Cell* cell)
{
    CellValue value = cellValue(cell);

    float x = rect.x + rect.width / 2.75;
    const float y = rect.y + rect.width / 5;
    const int fontSize = rect.width / 1.4;
    const Color color = colors[value];

    char str[2];

    if (value == 1)
        x = rect.x + rect.width / 2.2;

    if (cellContainsBomb(cell))
        sprintf(str, "*");
    else
        sprintf(str, "%d", value);

    DrawText(str, x, y, fontSize, color);
}
