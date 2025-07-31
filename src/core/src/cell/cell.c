#include "cell.h"
#include "stdlib.h"

Cell* allocateCell()
{
    Cell* cell = malloc(sizeof(struct cell));

    if (!cell)
        return NULL;

    cell->isOpened = false;
    cell->isMarked = false;
    cell->value = 0;

    cell->neighbours = malloc(sizeof(Cell*) * 8);

    if (!cell->neighbours)
    {
        free(cell);
        return NULL;
    }

    return cell;
}

void freeCell(Cell* cell)
{
    free(cell->neighbours);
    free(cell);
}