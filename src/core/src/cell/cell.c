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

int cellI(const Cell* cell)
{
    return cell->i;
}

int cellJ(const Cell* cell)
{
    return cell->j;
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

void toggleCellMark(Cell* cell)
{
    cell->isMarked = !cell->isMarked;
}

bool cellContainsBomb(const Cell* cell)
{
    return cell->value == BOMB;
}

CellValue cellValue(const Cell* cell)
{
    return cell->value;
}

void setCellValue(Cell* cell, CellValue value)
{
    cell->value = value;
}

void setCellIndexes(Cell* cell, int i, int j)
{
    cell->i = i;
    cell->j = j;
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
    if (cellContainsBomb(cell))
        return;

    CellValue value = 0;

    for (int i = 0; i < NEIGHBOURS_COUNT; i++)
        if (cell->neighbours[i] && cellContainsBomb(cell->neighbours[i]))
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