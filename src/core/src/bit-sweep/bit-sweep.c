#include "bit-sweep.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define WIDTH 10
#define HEIGHT 10
#define BOMB_COUNT 10

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

struct BitSweep
{
    int width;
    int height;
    int bombCount;
    Cell*** cells;
};

static void initializeCells(BitSweep* bitSweep);

void initializeBombIndexes(const BitSweep* bitSweep, int bombIndexes[]);

static void placeBombs(BitSweep* bitSweep, int bombsIndexes[]);

static void assignCellValues(BitSweep* bitSweep, int bombIndexes[]);

BitSweep* allocateBitSweep()
{
    BitSweep* bitSweep = malloc(sizeof(struct BitSweep));

    if (!bitSweep)
        return NULL;

    bitSweep->width = WIDTH;
    bitSweep->height = HEIGHT;
    bitSweep->bombCount = BOMB_COUNT;

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

    initializeCells(bitSweep);

    return bitSweep;
}

int bitSweepWidth(const BitSweep* bitSweep)
{
    return bitSweep->width;
}

int bitSweepHeight(const BitSweep* bitSweep)
{
    return bitSweep->height;
}

int bitSweepBombCount(const BitSweep* bitSweep)
{
    return bitSweep->bombCount;
}

Cell*** bitSweepCells(const BitSweep* bitSweep)
{
    return bitSweep->cells;
}

void printBitSweep(const BitSweep* bitSweep)
{
    printf("\n");

    for (int i = 0; i < bitSweep->width; i++)
    {
        for (int j = 0; j < bitSweep->height; j++)
        {
            if (cellValue(bitSweep->cells[i][j]) != BOMB)
                printf("%d ", cellValue(bitSweep->cells[i][j]));
            else
                printf("* ");
        }

        printf("\n");
    }
}

void freeBitSweep(BitSweep* bitSweep)
{
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
            freeCell(bitSweep->cells[i][j]);

        free(bitSweep->cells[i]);
    }

    free(bitSweep->cells);
    free(bitSweep);
}

static void initializeCells(BitSweep* bitSweep)
{
    srand(time(NULL));

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
        const int rIndex = rand() % (bitSweep->width * bitSweep->height);

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
            Cell* cell = bitSweep->cells[i][j];

            setCellPosition(cell, i, j);

            const int index = bitSweep->height * i + j;

            for (int k = 0; k < bitSweep->bombCount; k++)
                if (bombsIndexes[k] == index)
                    setCellValue(cell, BOMB);
        }
    }
}

static void assignCellValues(BitSweep* bitSweep, int bombIndexes[])
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