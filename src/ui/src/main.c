#include "bit-sweep-widget.h"
#include "bit-sweep.h"
#include "cell-widget.h"
#include "config.h"
#include "raylib.h"
#include "time.h"

void main()
{
    InitWindow(WIDTH, WIDTH, "BitSweeper");
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