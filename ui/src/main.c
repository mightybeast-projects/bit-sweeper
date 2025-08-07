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

    const int seed = time(NULL);
    const int cols = 20;
    const int rows = 20;
    const int bombCount = 60;
    BitSweepParams params = { seed, cols, rows, bombCount };
    BitSweepWidget* widget = allocateBitSweepWidget(params);

    while (!WindowShouldClose())
    {
        ClearBackground((Color) { 46, 46, 46, 255 });
        BeginDrawing();

        drawBitSweepWidget(widget);

        if (bitSweepIsFinished(widget->bitSweep) && IsKeyDown(KEY_R))
        {
            freeBitSweepWidget(widget);
            params.seed += time(NULL);
            widget = allocateBitSweepWidget(params);
        }

        EndDrawing();
    }

    CloseWindow();

    freeBitSweepWidget(widget);
}