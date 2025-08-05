#include "bit-sweep.h"
#include "cell-widget.h"
#include "raylib.h"

void main()
{
    InitWindow(600, 600, "XOGame");
    SetTargetFPS(60);

    const Color bg = { 46, 46, 46, 255 };

    while (!WindowShouldClose())
    {
        ClearBackground(bg);
        BeginDrawing();

        int cellCount = 9;
        int margin = 3;
        int size = (600 - 2 * margin * cellCount) / cellCount;

        for (int i = 0; i < cellCount; i++)
        {
            Rectangle rect = { margin + i * size + margin * i, margin, size, size };

            CellWidget* widget = allocateCellWidget(rect);

            setCellValue(widget->cell, i);
            openCell(widget->cell);
            drawCellWidget(widget);

            freeCellWidget(widget);
        }

        Rectangle r = { margin, margin * 2 + size, size, size };
        CellWidget* openedCellWidget = allocateCellWidget(r);
        drawCellWidget(openedCellWidget);

        freeCellWidget(openedCellWidget);

        EndDrawing();
    }

    CloseWindow();
}