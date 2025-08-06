#include "bit-sweep-widget.h"
#include "bit-sweep.h"
#include "cell-widget.h"
#include "raylib.h"

void main()
{
    InitWindow(500, 500, "BitSweeper");
    SetTargetFPS(60);

    BitSweepParams params = { 1, 10, 10, 10 };
    BitSweepWidget* widget = allocateBitSweepWidget(params);

    while (!WindowShouldClose())
    {
        ClearBackground((Color) { 46, 46, 46, 255 });
        BeginDrawing();

        drawBitSweepWidget(widget);

        EndDrawing();
    }

    CloseWindow();
}