#include "stdbool.h"

typedef struct cell Cell;

struct cell
{
    bool isOpened;
    bool isMarked;
    int value;
    Cell** neighbours;
};

Cell* allocateCell();
void freeCell(Cell* cell);