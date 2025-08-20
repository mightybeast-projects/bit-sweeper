#include "bit-sweep-widget.h"
#include "bit-sweep.h"
#include "cell-widget.h"
#include "config.h"
#include "raylib.h"
#include "time.h"

BitSweepWidget* widget;

static void createNewGame(void);

void main(void)
{
    InitWindow(WIDTH, WIDTH, "BitSweeper");
    SetTargetFPS(60);

    createNewGame();

    while (!WindowShouldClose()) {
        ClearBackground((Color) { 46, 46, 46, 255 });
        BeginDrawing();

        drawBitSweepWidget(widget);

        if (bitSweepIsFinished(widget->bitSweep) && IsKeyDown(KEY_R)) {
            freeBitSweepWidget(widget);

            createNewGame();
        }

        EndDrawing();
    }

    CloseWindow();

    freeBitSweepWidget(widget);
}

void createNewGame(void)
{
    BitSweepParams params = { time(NULL), COLS, COLS, BOMB_COUNT };

    widget = allocateBitSweepWidget(params);
}