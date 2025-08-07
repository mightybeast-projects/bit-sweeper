#include "bit-sweep.h"
#include "bit-sweep-internal.h"
#include "stdlib.h"

static void openCellNeighbours(BitSweep* const bitSweep, const Cell* const cell);

unsigned bitSweepWidth(const BitSweep* const bitSweep)
{
    return bitSweep->width;
}

unsigned bitSweepHeight(const BitSweep* const bitSweep)
{
    return bitSweep->height;
}

unsigned bitSweepBombCount(const BitSweep* const bitSweep)
{
    return bitSweep->bombCount;
}

int bitSweepOpenedCellsCount(const BitSweep* const bitSweep)
{
    return bitSweep->openedCellsCount;
}

int bitSweepNonBombCellsCount(const BitSweep* const bitSweep)
{
    return bitSweep->width * bitSweep->height - bitSweep->bombCount;
}

bool bitSweepIsFinished(const BitSweep* const bitSweep)
{
    return bitSweep->isFinished;
}

Cell*** bitSweepCells(const BitSweep* const bitSweep)
{
    return bitSweep->cells;
}

Cell* openCellAt(BitSweep* const bitSweep, const int i, const int j)
{
    Cell* cell = bitSweep->cells[i][j];

    if (cellIsOpened(cell) || bitSweep->isFinished || cellIsMarked(cell))
        return cell;

    openCell(cell);

    bitSweep->openedCellsCount++;

    const int nonBombCellsCount = bitSweepNonBombCellsCount(bitSweep);
    const bool gameWon = bitSweep->openedCellsCount == nonBombCellsCount;
    const bool gameLost = cellContainsBomb(cell);

    if (gameWon || gameLost)
    {
        bitSweep->isFinished = true;
        return cell;
    }

    if (cellValue(cell) == ZERO)
        openCellNeighbours(bitSweep, cell);

    return cell;
}

Cell* toggleCellMarkAt(BitSweep* const bitSweep, const int i, const int j)
{
    Cell* cell = bitSweep->cells[i][j];

    if (!cellIsOpened(cell) && !bitSweep->isFinished)
        toggleCellMark(cell);

    return cell;
}

static void openCellNeighbours(BitSweep* const bitSweep, const Cell* const cell)
{
    Cell** neighbours = cellNeighbours(cell);

    for (; *neighbours; neighbours++)
    {
        const Cell* neighbour = *neighbours;
        const int i = cellI(neighbour);
        const int j = cellJ(neighbour);

        if (!cellIsOpened(neighbour) && !cellContainsBomb(neighbour))
            openCellAt(bitSweep, i, j);
    }
}