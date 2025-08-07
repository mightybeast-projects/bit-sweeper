#include "bit-sweep-allocator.h"
#include "bit-sweep-internal.h"
#include "safe-memory.h"
#include "stdlib.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

static Cell*** allocateCells(BitSweep* const bitSweep);
static void initializeCells(BitSweep* const bitSweep);
static void initializeBombIndexes(const BitSweep* const bitSweep, int bombIndexes[]);
static void placeBombs(BitSweep* const bitSweep, int bombsIndexes[]);
static void assignCellValues(BitSweep* const bitSweep);
static void assignCellValue(BitSweep* const bitSweep, const int i, const int j);

BitSweep* allocateBitSweep(const BitSweepParams params)
{
    if (params.bombCount > params.cols * params.rows)
        return NULL;

    BitSweep* bitSweep = safeMalloc(sizeof(struct BitSweep));

    bitSweep->width = params.cols;
    bitSweep->height = params.rows;
    bitSweep->bombCount = params.bombCount;
    bitSweep->isFinished = false;
    bitSweep->openedCellsCount = 0;
    bitSweep->cells = allocateCells(bitSweep);

    srand(params.seed);

    initializeCells(bitSweep);

    return bitSweep;
}

void freeBitSweep(BitSweep* const bitSweep)
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

static Cell*** allocateCells(BitSweep* const bitSweep)
{
    Cell*** cells = safeMalloc(sizeof(Cell**) * bitSweep->width);

    for (int i = 0; i < bitSweep->width; i++)
    {
        cells[i] = safeMalloc(sizeof(Cell*) * bitSweep->height);

        for (int j = 0; j < bitSweep->height; j++)
        {
            Cell* cell = allocateCell();

            setCellIndexes(cell, i, j);

            cells[i][j] = cell;
        }
    }

    return cells;
}

static void initializeCells(BitSweep* const bitSweep)
{
    unsigned* bombIndexes = safeMalloc(sizeof(unsigned) * bitSweep->bombCount);

    initializeBombIndexes(bitSweep, bombIndexes);
    placeBombs(bitSweep, bombIndexes);
    assignCellValues(bitSweep);

    free(bombIndexes);
}

static void initializeBombIndexes(const BitSweep* const bitSweep, int bombIndexes[])
{
    for (int i = 0; i < bitSweep->bombCount; i++)
    {
        const int rIndex = rand() % (bitSweep->width * bitSweep->height);

        bool duplicated = false;

        for (int j = 0; j < i; j++)
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

static void placeBombs(BitSweep* const bitSweep, int bombsIndexes[])
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

static void assignCellValues(BitSweep* const bitSweep)
{
    for (int i = 0; i < bitSweep->width; i++)
        for (int j = 0; j < bitSweep->height; j++)
            assignCellValue(bitSweep, i, j);
}

static void assignCellValue(BitSweep* const bitSweep, const int i, const int j)
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