#include "bit-sweep-printer.h"
#include "stdio.h"

static void printCellValues(const BitSweep* bitSweep);

static void printCells(const BitSweep* bitSweep);

void printBitSweep(const BitSweep* bitSweep)
{
    printf("\n");
    printCellValues(bitSweep);
    printf("\n");
    printCells(bitSweep);
    printf("\n");
}

static void printCellValues(const BitSweep* bitSweep)
{
    Cell*** cells = bitSweep->cells;

    for (int i = 0; i < bitSweep->width; i++)
    {
        for (int j = 0; j < bitSweep->height; j++)
        {
            if (cellValue(cells[i][j]) == ZERO)
                printf(". ");
            else if (!cellContainsBomb(cells[i][j]))
                printf("%d ", cellValue(cells[i][j]));
            else
                printf("* ");
        }

        printf("\n");
    }
}

static void printCells(const BitSweep* bitSweep)
{
    Cell*** cells = bitSweep->cells;

    for (int i = 0; i < bitSweep->width; i++)
    {
        for (int j = 0; j < bitSweep->height; j++)
        {
            Cell* cell = cells[i][j];

            if (cellIsOpened(cell) && cellContainsBomb(cell))
                printf("* ");
            else if (!cellIsOpened(cell) && !cellIsMarked(cell))
                printf(". ");
            else if (cellIsMarked(cell))
                printf("! ");
            else
                printf("%d ", cellValue(cell));
        }

        printf("\n");
    }
}