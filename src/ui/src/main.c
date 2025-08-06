#include "bit-sweep.h"
#include "cell-widget.h"
#include "raylib.h"

CellWidget* cells[20];

void initCellWidgets()
{
    int margin = 3;
    int size = 45;

    for (int i = 0; i < 10; i++)
    {
        Rectangle rect = { margin + i * size + margin * i, margin, size, size };

        CellWidget* widget = allocateCellWidget(rect);

        setCellValue(widget->cell, i);
        openCell(widget->cell);

        cells[i] = widget;
    }

    Rectangle r;
    CellWidget* w;

    r = (Rectangle) { margin, margin * 2 + size, size, size };
    w = allocateCellWidget(r);
    cells[10] = w;

    r = (Rectangle) { margin + size + margin, margin * 2 + size, size, size };
    w = allocateCellWidget(r);
    toggleCellMark(w->cell);
    cells[11] = w;

    for (int i = 0; i < 10; i++)
    {
        Rectangle rect = { margin + i * size + margin * i, margin * 3 + size * 2, size, size };

        CellWidget* widget = allocateCellWidget(rect);

        setCellValue(widget->cell, i);

        cells[12 + i] = widget;
    }
}

void main()
{
    InitWindow(600, 600, "XOGame");
    SetTargetFPS(60);

    initCellWidgets();

    const Color bg = { 46, 46, 46, 255 };

    while (!WindowShouldClose())
    {
        ClearBackground(bg);
        BeginDrawing();

        for (int i = 0; i < 22; i++)
            handleCellWidgetInput(cells[i]);

        for (int i = 0; i < 22; i++)
            drawCellWidget(cells[i]);

        EndDrawing();
    }

    for (int i = 0; i < 22; i++)
        freeCellWidget(cells[i]);

    CloseWindow();
}