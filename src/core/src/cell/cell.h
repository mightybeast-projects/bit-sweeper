#include "stdbool.h"

typedef enum
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
} CellValue;

typedef struct Cell Cell;

Cell* allocateCell();

bool cellIsOpened(const Cell* cell);

void openCell(Cell* cell);

bool cellIsMarked(const Cell* cell);

CellValue cellValue(const Cell* cell);

void setCellValue(Cell* cell, CellValue value);

void setCellPosition(Cell* cell, unsigned x, unsigned y);

Cell** cellNeighbours(const Cell* cell);

void addCellNeighbour(Cell* cell, Cell* neighbour);

void calculateCellValue(Cell* cell);

void freeCell(Cell* cell);