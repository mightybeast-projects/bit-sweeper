#include "cell.h"
#include "stdlib.h"

#define NEIGHBOURS_COUNT 8

Cell* allocateCell()
{
    Cell* cell = malloc(sizeof(struct cell));

    if (!cell)
        return NULL;

    cell->isOpened = false;
    cell->isMarked = false;
    cell->value = ZERO;

    cell->neighbours = malloc(sizeof(Cell*) * NEIGHBOURS_COUNT);

    if (!cell->neighbours)
    {
        free(cell);
        return NULL;
    }

    for (int i = 0; i < NEIGHBOURS_COUNT; i++)
        cell->neighbours[i] = NULL;

    return cell;
}

void addNeighbour(Cell* cell, Cell* neighbour)
{
    Cell** ptr = cell->neighbours;
    int nCount = 0;

    while (*ptr && nCount < NEIGHBOURS_COUNT)
    {
        if (*ptr == neighbour)
            return;

        ptr++;
        nCount++;
    }

    if (nCount == NEIGHBOURS_COUNT)
        return;

    *ptr = neighbour;
}

void syncValue(Cell* cell) { }

void freeCell(Cell* cell)
{
    if (!cell)
        return;

    free(cell->neighbours);
    free(cell);
}