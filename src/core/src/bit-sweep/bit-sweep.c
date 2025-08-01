#include "bit-sweep.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

struct BitSweep
{
    unsigned int width;
    unsigned int height;
    unsigned int bombCount;
    Cell*** cells;
};

static void initializeCells(BitSweep* bitSweep);

static void initializeBombIndexes(const BitSweep* bitSweep, int bombIndexes[]);

static void placeBombs(BitSweep* bitSweep, int bombsIndexes[]);

static void assignCellValues(BitSweep* bitSweep, int bombIndexes[]);

BitSweep* allocateBitSweep(BitSweepParams params)
{
    BitSweep* bitSweep = malloc(sizeof(struct BitSweep));

    if (!bitSweep)
        return NULL;

    bitSweep->width = params.cols;
    bitSweep->height = params.rows;
    bitSweep->bombCount = params.bombCount;

    bitSweep->cells = malloc(sizeof(Cell**) * bitSweep->width);

    if (!bitSweep->cells)
    {
        free(bitSweep);
        return NULL;
    }

    for (int i = 0; i < bitSweep->width; i++)
    {
        bitSweep->cells[i] = malloc(sizeof(Cell*) * bitSweep->height);

        for (int j = 0; j < bitSweep->height; j++)
            bitSweep->cells[i][j] = allocateCell();
    }

    srand(params.seed);

    initializeCells(bitSweep);

    return bitSweep;
}

unsigned int bitSweepWidth(const BitSweep* bitSweep)
{
    return bitSweep->width;
}

unsigned int bitSweepHeight(const BitSweep* bitSweep)
{
    return bitSweep->height;
}

unsigned int bitSweepBombCount(const BitSweep* bitSweep)
{
    return bitSweep->bombCount;
}

Cell*** bitSweepCells(const BitSweep* bitSweep)
{
    return bitSweep->cells;
}

bool openCellAt(BitSweep* bitSweep, const int x, const int y)
{
    Cell* cell = bitSweep->cells[x][y];

    openCell(cell);

    return cellValue(cell) != BOMB;
}

void printBitSweep(const BitSweep* bitSweep)
{
    printf("\n");

    for (int i = 0; i < bitSweep->width; i++)
    {
        for (int j = 0; j < bitSweep->height; j++)
        {
            if (cellValue(bitSweep->cells[i][j]) == ZERO)
                printf(". ");
            else if (cellValue(bitSweep->cells[i][j]) != BOMB)
                printf("%d ", cellValue(bitSweep->cells[i][j]));
            else
                printf("* ");
        }

        printf("\n");
    }

    printf("\n");
}

void freeBitSweep(BitSweep* bitSweep)
{
    for (int i = 0; i < bitSweep->width; i++)
    {
        for (int j = 0; j < bitSweep->height; j++)
            freeCell(bitSweep->cells[i][j]);

        free(bitSweep->cells[i]);
    }

    free(bitSweep->cells);
    free(bitSweep);
}

void initializeCells(BitSweep* bitSweep)
{
    int* bombIndexes = malloc(sizeof(int) * bitSweep->bombCount);

    if (!bombIndexes)
        return;

    initializeBombIndexes(bitSweep, bombIndexes);
    placeBombs(bitSweep, bombIndexes);
    assignCellValues(bitSweep, bombIndexes);

    free(bombIndexes);
}

void initializeBombIndexes(const BitSweep* bitSweep, int bombIndexes[])
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

void placeBombs(BitSweep* bitSweep, int bombsIndexes[])
{
    for (int i = 0; i < bitSweep->width; i++)
    {
        for (int j = 0; j < bitSweep->height; j++)
        {
            Cell* cell = bitSweep->cells[i][j];

            setCellPosition(cell, i, j);

            const int index = bitSweep->height * i + j;

            for (int k = 0; k < bitSweep->bombCount; k++)
                if (bombsIndexes[k] == index)
                    setCellValue(cell, BOMB);
        }
    }
}

void assignCellValues(BitSweep* bitSweep, int bombIndexes[])
{
    for (int i = 0; i < bitSweep->width; i++)
    {
        for (int j = 0; j < bitSweep->height; j++)
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
    }
}