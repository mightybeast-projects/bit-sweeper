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

Cell* allocateCell(void);

unsigned int cellI(const Cell* cell);

unsigned int cellJ(const Cell* cell);

bool cellIsOpened(const Cell* cell);

void openCell(Cell* cell);

bool cellIsMarked(const Cell* cell);

void toggleCellMark(Cell* cell);

bool cellContainsBomb(const Cell* cell);

CellValue cellValue(const Cell* cell);

void setCellValue(Cell* cell, CellValue value);

void setCellIndexes(Cell* cell, unsigned i, unsigned j);

Cell** cellNeighbours(const Cell* cell);

void addCellNeighbour(Cell* cell, Cell* neighbour);

void calculateCellValue(Cell* cell);

void freeCell(Cell* cell);