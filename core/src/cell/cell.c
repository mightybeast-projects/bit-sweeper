#include "cell.h"
#include "safe-memory.h"

#define NEIGHBOURS_COUNT 8

struct Cell
{
    int i;
    int j;
    bool isOpened;
    bool isMarked;
    CellValue value;
    Cell** neighbours;
};

Cell* allocateCell(void)
{
    Cell* cell = safeMalloc(sizeof(struct Cell));

    cell->i = 0;
    cell->j = 0;
    cell->isOpened = false;
    cell->isMarked = false;
    cell->value = ZERO;
    cell->neighbours = safeMalloc(sizeof(Cell*) * (NEIGHBOURS_COUNT + 1));

    for (int i = 0; i < NEIGHBOURS_COUNT + 1; i++)
        cell->neighbours[i] = NULL;

    return cell;
}

void freeCell(Cell* const cell)
{
    if (!cell)
        return;

    free(cell->neighbours);
    free(cell);
}

int cellI(const Cell* const cell)
{
    return cell->i;
}

int cellJ(const Cell* const cell)
{
    return cell->j;
}

void setCellIndexes(Cell* const cell, int i, int j)
{
    cell->i = i;
    cell->j = j;
}

bool cellIsOpened(const Cell* const cell)
{
    return cell->isOpened;
}

void openCell(Cell* cell)
{
    cell->isOpened = true;
}

bool cellIsMarked(const Cell* const cell)
{
    return cell->isMarked;
}

void toggleCellMark(Cell* cell)
{
    cell->isMarked = !cell->isMarked;
}

bool cellContainsBomb(const Cell* const cell)
{
    return cell->value == BOMB;
}

CellValue cellValue(const Cell* const cell)
{
    return cell->value;
}

void setCellValue(Cell* const cell, CellValue value)
{
    cell->value = value;
}

Cell** cellNeighbours(const Cell* const cell)
{
    return cell->neighbours;
}

void addCellNeighbour(Cell* const cell, Cell* const neighbour)
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

void calculateCellValue(Cell* const cell)
{
    if (cellContainsBomb(cell))
        return;

    CellValue value = 0;

    for (int i = 0; i < NEIGHBOURS_COUNT; i++)
        if (cell->neighbours[i] && cellContainsBomb(cell->neighbours[i]))
            value++;

    cell->value = value;
}