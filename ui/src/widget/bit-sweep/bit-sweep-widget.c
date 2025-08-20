#include "bit-sweep-widget.h"
#include "config.h"
#include "safe-memory.h"

static CellWidget*** allocateCellsWidgets(BitSweep* const bitSweep);

static void drawRestartMessage(void);

BitSweepWidget* allocateBitSweepWidget(const BitSweepParams params)
{
    BitSweepWidget* widget = safeMalloc(sizeof(struct BitSweepWidget));
    BitSweep* bitSweep = allocateBitSweep(params);

    widget->bitSweep = bitSweep;
    widget->cellsWidgets = allocateCellsWidgets(bitSweep);

    return widget;
}

void freeBitSweepWidget(BitSweepWidget* const widget)
{
    BitSweep* bitSweep = widget->bitSweep;
    CellWidget*** cellsWidgets = widget->cellsWidgets;

    for (int i = 0; i < bitSweepWidth(bitSweep); i++) {
        for (int j = 0; j < bitSweepHeight(bitSweep); j++)
            if (cellsWidgets[i][j])
                freeCellWidget(cellsWidgets[i][j]);

        if (cellsWidgets[i])
            free(cellsWidgets[i]);
    }

    free(cellsWidgets);
    freeBitSweep(bitSweep);
    free(widget);
}

void drawBitSweepWidget(const BitSweepWidget* const widget)
{
    CellWidget*** cellsWidgets = widget->cellsWidgets;

    const int width = bitSweepWidth(widget->bitSweep);
    const int height = bitSweepHeight(widget->bitSweep);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            handleCellWidgetInput(cellsWidgets[i][j]);
            drawCellWidget(cellsWidgets[i][j]);
        }
    }

    if (bitSweepIsFinished(widget->bitSweep))
        drawRestartMessage();
}

static CellWidget*** allocateCellsWidgets(BitSweep* const bitSweep)
{
    const int width = bitSweepWidth(bitSweep);
    const int height = bitSweepHeight(bitSweep);

    CellWidget*** cellsWidgets = safeMalloc(sizeof(CellWidget**) * width);

    const float margin = 2;
    const float size = (WIDTH - (width - 1) * margin - margin * 2) / width;

    for (int i = 0; i < width; i++) {
        cellsWidgets[i] = safeMalloc(sizeof(CellWidget*) * height);

        for (int j = 0; j < height; j++) {
            float x = i * (size + margin) + margin;
            float y = j * (size + margin) + margin;
            Rectangle rect = { x, y, size, size };

            Cell* cell = bitSweepCells(bitSweep)[i][j];

            CellWidget* cellWidget = allocateCellWidget(rect, cell, bitSweep);

            cellsWidgets[i][j] = cellWidget;
        }
    }

    return cellsWidgets;
}

static void drawRestartMessage(void)
{
    const int fontSize = 30;
    const char* str = "Press R to restart.";
    const int textWidth = MeasureText(str, fontSize);
    const int x = WIDTH / 2 - textWidth / 2;
    const int y = WIDTH / 2 + textWidth / 2;

    DrawText(str, x, y, fontSize, WHITE);
}