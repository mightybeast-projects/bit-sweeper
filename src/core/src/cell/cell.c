#include "cell.h"
#include "stdlib.h"

#define NEIGHBOURS_COUNT 8

struct Cell
{
    int x;
    int y;
    bool isOpened;
    bool isMarked;
    CellValue value;
    Cell** neighbours;
};

Cell* allocateCell()
{
    Cell* cell = malloc(sizeof(struct Cell));

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

bool cellIsOpened(const Cell* cell)
{
    return cell->isOpened;
}

void openCell(Cell* cell)
{
    cell->isOpened = true;
}

bool cellIsMarked(const Cell* cell)
{
    return cell->isMarked;
}

CellValue cellValue(const Cell* cell)
{
    return cell->value;
}

void setCellValue(Cell* cell, CellValue value)
{
    cell->value = value;
}

void setCellPosition(Cell* cell, int x, int y)
{
    cell->x = x;
    cell->y = y;
}

Cell** cellNeighbours(const Cell* cell)
{
    return cell->neighbours;
}

void addCellNeighbour(Cell* cell, Cell* neighbour)
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

void calculateCellValue(Cell* cell)
{
    if (cell->value == BOMB)
        return;

    CellValue value = 0;

    for (int i = 0; i < NEIGHBOURS_COUNT; i++)
        if (cell->neighbours[i] && cell->neighbours[i]->value == BOMB)
            value++;

    cell->value = value;
}

void freeCell(Cell* cell)
{
    if (!cell)
        return;

    free(cell->neighbours);
    free(cell);
}