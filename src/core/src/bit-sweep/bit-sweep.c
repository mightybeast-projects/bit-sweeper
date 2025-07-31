#include "bit-sweep.h"
#include "stdlib.h"

#define WIDTH 10
#define HEIGHT 10
#define BOMB_COUNT 10

BitSweep* allocateBitSweep()
{
    BitSweep* bitSweep = malloc(sizeof(struct bitSweep));

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

    return bitSweep;
}

void freeBitSweep(BitSweep* bitSweep)
{
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            freeCell(bitSweep->cells[i][j]);
        }

        free(bitSweep->cells[i]);
    }

    free(bitSweep->cells);
    free(bitSweep);
}
