#include "bit-sweep.h"
#include "stdlib.h"

static void openCellNeighbours(BitSweep* bitSweep, const Cell* cell);

unsigned bitSweepWidth(const BitSweep* bitSweep)
{
    return bitSweep->width;
}

unsigned bitSweepHeight(const BitSweep* bitSweep)
{
    return bitSweep->height;
}

unsigned bitSweepBombCount(const BitSweep* bitSweep)
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
    Cell* cell = bitSweep->cells[i][j];

    if (cellIsOpened(cell) || bitSweep->isFinished || cellIsMarked(cell))
        return cell;

    openCell(cell);

    bitSweep->openedCellsCount++;

    bool gameWon = bitSweep->openedCellsCount == bitSweepNonBombCellsCount(bitSweep);
    bool gameLost = cellContainsBomb(cell);

    if (gameWon || gameLost)
    {
        bitSweep->isFinished = true;
        return cell;
    }

    if (cellValue(cell) == ZERO)
        openCellNeighbours(bitSweep, cell);

    return cell;
}

Cell* toggleCellMarkAt(BitSweep* bitSweep, const int i, const int j)
{
    Cell* cell = bitSweep->cells[i][j];

    if (!cellIsOpened(cell) && !bitSweep->isFinished)
        toggleCellMark(cell);

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

        if (!cellIsOpened(neighbour) && !cellContainsBomb(neighbour))
            openCellAt(bitSweep, i, j);
    }
}