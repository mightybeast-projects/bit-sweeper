#include "stdbool.h"

enum CellValue
{
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    BOMB
};

typedef struct cell Cell;

struct cell
{
    int x;
    int y;
    bool isOpened;
    bool isMarked;
    enum CellValue value;
    Cell** neighbours;
};

Cell* allocateCell();

void addNeighbour(Cell* cell, Cell* neighbour);

void freeCell(Cell* cell);