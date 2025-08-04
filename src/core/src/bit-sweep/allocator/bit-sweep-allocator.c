#include "bit-sweep-allocator.h"
#include "stdlib.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

static void allocateCells(BitSweep* bitSweep);

static void initializeCells(BitSweep* bitSweep);

static void initializeBombIndexes(const BitSweep* bitSweep, int bombIndexes[]);

static void placeBombs(BitSweep* bitSweep, int bombsIndexes[]);

static void assignCellValues(BitSweep* bitSweep);

static void assignCellValue(BitSweep* bitSweep, const int i, const int j);

BitSweep* allocateBitSweep(BitSweepParams params)
{
    BitSweep* bitSweep = malloc(sizeof(struct BitSweep));

    if (!bitSweep)
        return NULL;

    bitSweep->width = params.cols;
    bitSweep->height = params.rows;
    bitSweep->bombCount = params.bombCount;

    allocateCells(bitSweep);

    if (!bitSweep->cells)
    {
        freeBitSweep(bitSweep);
        return NULL;
    }

    srand(params.seed);

    initializeCells(bitSweep);

    return bitSweep;
}

void freeBitSweep(BitSweep* bitSweep)
{
    if (!bitSweep)
        return;

    for (int i = 0; i < bitSweep->width; i++)
    {
        for (int j = 0; j < bitSweep->height; j++)
            if (bitSweep->cells[i][j])
                freeCell(bitSweep->cells[i][j]);

        if (bitSweep->cells[i])
            free(bitSweep->cells[i]);
    }

    free(bitSweep->cells);
    free(bitSweep);
}

static void allocateCells(BitSweep* bitSweep)
{
    bitSweep->cells = malloc(sizeof(Cell**) * bitSweep->width);

    if (!bitSweep->cells)
        return;

    for (int i = 0; i < bitSweep->width; i++)
    {
        bitSweep->cells[i] = malloc(sizeof(Cell*) * bitSweep->height);

        if (!bitSweep->cells[i])
        {
            for (int j = 0; j < i; j++)
            {
                for (int k = 0; k < bitSweep->height; k++)
                    if (bitSweep->cells[j][k])
                        free(bitSweep->cells[j][k]);

                free(bitSweep->cells[j]);
            }

            free(bitSweep->cells);
            bitSweep->cells = NULL;
            return;
        }

        for (int j = 0; j < bitSweep->height; j++)
        {
            Cell* cell = allocateCell();

            if (!cell)
                continue;

            setCellIndexes(cell, i, j);

            bitSweep->cells[i][j] = cell;
        }
    }
}

static void initializeCells(BitSweep* bitSweep)
{
    int* bombIndexes = malloc(sizeof(int) * bitSweep->bombCount);

    if (!bombIndexes)
        return;

    initializeBombIndexes(bitSweep, bombIndexes);
    placeBombs(bitSweep, bombIndexes);
    assignCellValues(bitSweep);

    free(bombIndexes);
}

static void initializeBombIndexes(const BitSweep* bitSweep, int bombIndexes[])
{
    for (int i = 0; i < bitSweep->bombCount; i++)
    {
        const unsigned rIndex = rand() % (bitSweep->width * bitSweep->height);

        bool duplicated = false;

        for (int j = 0; j < bitSweep->bombCount; j++)
        {
            if (bombIndexes[j] == rIndex)
            {
                duplicated = true;
                break;
            }
        }

        if (duplicated)
        {
            i--;
            continue;
        }

        bombIndexes[i] = rIndex;
    }
}

static void placeBombs(BitSweep* bitSweep, int bombsIndexes[])
{
    for (int i = 0; i < bitSweep->width; i++)
    {
        for (int j = 0; j < bitSweep->height; j++)
        {
            const int index = bitSweep->height * i + j;

            for (int k = 0; k < bitSweep->bombCount; k++)
                if (bombsIndexes[k] == index)
                    setCellValue(bitSweep->cells[i][j], BOMB);
        }
    }
}

static void assignCellValues(BitSweep* bitSweep)
{
    for (int i = 0; i < bitSweep->width; i++)
        for (int j = 0; j < bitSweep->height; j++)
            assignCellValue(bitSweep, i, j);
}

static void assignCellValue(BitSweep* bitSweep, const int i, const int j)
{
    Cell* cell = bitSweep->cells[i][j];

    const int minX = MAX(0, i - 1);
    const int maxX = MIN(i + 1, bitSweep->width - 1);

    const int minJ = MAX(0, j - 1);
    const int maxJ = MIN(j + 1, bitSweep->height - 1);

    for (int k = minX; k <= maxX; k++)
    {
        for (int l = minJ; l <= maxJ; l++)
        {
            if (k == i && l == j)
                continue;

            addCellNeighbour(cell, bitSweep->cells[k][l]);
        }
    }

    calculateCellValue(cell);
}