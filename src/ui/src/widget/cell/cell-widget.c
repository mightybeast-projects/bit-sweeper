#include "cell-widget.h"
#include "safe-memory.h"
#include "stdio.h"

const static Color colors[10] = {
    BLANK, SKYBLUE, GREEN, PINK, PURPLE, ORANGE, BLUE, YELLOW, GRAY, BLACK
};

static void drawCellBackground(const CellWidget* widget, const Cell* cell);

static void drawCellMark(const Rectangle rect, const Cell* cell);

static void drawCellValue(const Rectangle rect, const Cell* cell);

CellWidget* allocateCellWidget(Rectangle rect)
{
    CellWidget* widget = safeMalloc(sizeof(struct CellWidget));

    widget->rect = rect;
    widget->cell = allocateCell();

    return widget;
}

void handleCellWidgetInput(CellWidget* widget)
{
    const Vector2 mousePos = GetMousePosition();
    const Rectangle rect = widget->rect;

    bool mouseCollides = CheckCollisionPointRec(mousePos, rect);

    widget->isClicked = IsMouseButtonDown(MOUSE_LEFT_BUTTON) && mouseCollides;

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && mouseCollides)
        openCell(widget->cell);

    if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON) && mouseCollides)
        toggleCellMark(widget->cell);
}

void drawCellWidget(const CellWidget* widget)
{
    Rectangle rect = widget->rect;
    Cell* cell = widget->cell;

    drawCellBackground(widget, cell);

    if (cellIsMarked(cell))
        drawCellMark(rect, cell);

    if (cellIsOpened(cell))
        drawCellValue(rect, cell);
}

void freeCellWidget(CellWidget* widget)
{
    freeCell(widget->cell);
    free(widget);
}

static void drawCellBackground(const CellWidget* widget, const Cell* cell)
{
    if (cellIsOpened(cell) && cellContainsBomb(cell))
        DrawRectangleRounded(widget->rect, 0.1, 10, RED);
    else if (cellIsOpened(cell) || widget->isClicked)
        DrawRectangleRounded(widget->rect, 0.1, 10, (Color) { 60, 60, 60, 255 });
    else if (!cellIsOpened(cell))
        DrawRectangleRounded(widget->rect, 0.1, 10, (Color) { 75, 75, 75, 255 });
}

static void drawCellMark(const Rectangle rect, const Cell* cell)
{
    int x = rect.x + rect.width / 2.05;
    int y = rect.y + rect.width / 5;
    int fontSize = rect.width / 1.5;

    DrawText("!", x, y, fontSize, RED);
}

static void drawCellValue(const Rectangle rect, const Cell* cell)
{
    CellValue value = cellValue(cell);

    int x = rect.x + rect.width / 2.75;
    int y = rect.y + rect.width / 5;
    int fontSize = rect.width / 1.5;
    Color color = colors[value];

    char str[2];

    if (value == 1)
        x = rect.x + rect.width / 2.2;

    if (cellContainsBomb(cell))
        sprintf(str, "*");
    else
        sprintf(str, "%d", value);

    DrawText(str, x, y, fontSize, color);
}
