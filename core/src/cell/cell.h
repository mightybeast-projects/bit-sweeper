#pragma once

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
void freeCell(Cell* const cell);

int cellI(const Cell* const cell);
int cellJ(const Cell* const cell);
void setCellIndexes(Cell* const cell, int i, int j);

bool cellIsOpened(const Cell* const cell);
void openCell(Cell* const cell);

bool cellIsMarked(const Cell* const cell);
void toggleCellMark(Cell* const cell);

bool cellContainsBomb(const Cell* const cell);

CellValue cellValue(const Cell* const cell);
void setCellValue(Cell* const cell, CellValue value);

Cell** cellNeighbours(const Cell* const cell);
void addCellNeighbour(Cell* const cell, Cell* const neighbour);

void calculateCellValue(Cell* const cell);