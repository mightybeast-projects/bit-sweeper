#include "bit-sweep-widget.h"
#include "config.h"
#include "safe-memory.h"

static CellWidget*** allocateCellsWidgets(BitSweep* bitSweep);

BitSweepWidget* allocateBitSweepWidget(BitSweepParams params)
{
    BitSweepWidget* widget = safeMalloc(sizeof(struct BitSweepWidget));
    BitSweep* bitSweep = allocateBitSweep(params);

    widget->bitSweep = bitSweep;
    widget->cellsWidgets = allocateCellsWidgets(bitSweep);

    return widget;
}

void drawBitSweepWidget(const BitSweepWidget* widget)
{
    CellWidget*** cellsWidgets = widget->cellsWidgets;

    int width = bitSweepWidth(widget->bitSweep);
    int height = bitSweepHeight(widget->bitSweep);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            handleCellWidgetInput(cellsWidgets[i][j]);
            drawCellWidget(cellsWidgets[i][j]);
        }
    }

    if (bitSweepIsFinished(widget->bitSweep))
    {
        const int fontSize = 30;
        const char* str = "Press R to restart.";
        const int textWidth = MeasureText(str, fontSize);
        const int x = WIDTH / 2 - textWidth / 2;
        const int y = WIDTH / 2 + textWidth / 2;

        DrawText(str, x, y, fontSize, WHITE);
    }
}

void freeBitSweepWidget(BitSweepWidget* widget)
{
    BitSweep* bitSweep = widget->bitSweep;
    CellWidget*** cellsWidgets = widget->cellsWidgets;

    for (int i = 0; i < bitSweepWidth(bitSweep); i++)
    {
        for (int j = 0; j < bitSweepHeight(bitSweep); j++)
            if (cellsWidgets[i][j])
                freeCellWidget(cellsWidgets[i][j]);

        if (cellsWidgets[i])
            free(cellsWidgets[i]);
    }

    free(widget->cellsWidgets);
    freeBitSweep(widget->bitSweep);
    free(widget);
}

static CellWidget*** allocateCellsWidgets(BitSweep* bitSweep)
{
    int width = bitSweepWidth(bitSweep);
    int height = bitSweepHeight(bitSweep);

    CellWidget*** cellsWidgets = safeMalloc(sizeof(CellWidget**) * width);

    int cellCount = width;
    float margin = 2;
    float size = (WIDTH - (cellCount - 1) * margin - margin * 2) / cellCount;

    for (int i = 0; i < width; i++)
    {
        cellsWidgets[i] = safeMalloc(sizeof(CellWidget*) * height);

        for (int j = 0; j < height; j++)
        {
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