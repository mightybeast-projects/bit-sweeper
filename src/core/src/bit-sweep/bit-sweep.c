#include "bit-sweep.h"
#include "stdlib.h"

static void openCellNeighbours(BitSweep* bitSweep, const Cell* cell);

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

int bitSweepOpenedCellsCount(const BitSweep* bitSweep)
{
    return bitSweep->openedCellsCount;
}

int bitSweepNonBombCellsCount(const BitSweep* bitSweep)
{
    return bitSweep->width * bitSweep->height - bitSweep->bombCount;
}

bool bitSweepIsFinished(const BitSweep* bitSweep)
{
    return bitSweep->isFinished;
}

Cell*** bitSweepCells(const BitSweep* bitSweep)
{
    return bitSweep->cells;
}

Cell* openCellAt(BitSweep* bitSweep, const int i, const int j)
{
    if (bitSweep->isFinished)
        return NULL;

    Cell* cell = bitSweep->cells[i][j];

    if (cellIsMarked(cell))
        return cell;

    openCell(cell);

    bitSweep->openedCellsCount++;

    if (bitSweep->openedCellsCount == bitSweepNonBombCellsCount(bitSweep))
    {
        bitSweep->isFinished = true;
        return cell;
    }

    if (cellContainsBomb(cell))
    {
        bitSweep->isFinished = true;
        return cell;
    }

    if (cellValue(cell) != ZERO)
        return cell;

    openCellNeighbours(bitSweep, cell);

    return cell;
}

static void openCellNeighbours(BitSweep* bitSweep, const Cell* cell)
{
    Cell** neighbours = cellNeighbours(cell);

    for (; *neighbours; neighbours++)
    {
        Cell* neighbour = *neighbours;
        int i = cellI(neighbour);
        int j = cellJ(neighbour);

        const bool canOpenCell = !cellIsOpened(neighbour)
            && !cellContainsBomb(neighbour) && !cellIsMarked(neighbour);

        if (canOpenCell)
            openCellAt(bitSweep, i, j);
    }
}