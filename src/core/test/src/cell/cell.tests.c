#include "cell.tests.h"
#include "cell.h"
#include "unity.h"

Cell* cell;

void setUpCell()
{
    cell = allocateCell();
}

void tearDownCell()
{
    freeCell(cell);
}

void Cell_Allocation_Should_Return_Allocated_Cell()
{
    TEST_ASSERT_NOT_NULL(cell);
}

void Allocated_Cell_Should_Not_Be_Opened_By_Default()
{
    TEST_ASSERT_FALSE(cellIsOpened(cell));
}

void Allocated_Cell_Should_Not_Be_Marked_By_Default()
{
    TEST_ASSERT_FALSE(cellIsMarked(cell));
}

void Allocated_Cell_Should_Have_Zero_Value_By_Default()
{
    TEST_ASSERT_EQUAL_INT(ZERO, cellValue(cell));
}

void Allocated_Cell_Should_Not_Have_Neighbours()
{
    Cell*** neighbours = cellNeighbours(cell);

    TEST_ASSERT_NOT_NULL(neighbours);

    for (int i = 0; i < sizeof(neighbours); i++)
        TEST_ASSERT_NULL(neighbours[i]);
}

void Cell_Should_Add_Neighbour_To_Itself()
{
    Cell* neighbour = allocateCell();

    addCellNeighbour(cell, neighbour);

    TEST_ASSERT_NOT_NULL(cellNeighbours(cell)[0]);

    freeCell(neighbour);
}

void Cell_Should_Not_Add_Same_Neighbour_More_Than_Once()
{
    Cell* neighbour = allocateCell();

    addCellNeighbour(cell, neighbour);
    addCellNeighbour(cell, neighbour);

    Cell*** neighbours = cellNeighbours(cell);

    TEST_ASSERT_NOT_NULL(neighbours[0]);
    TEST_ASSERT_NULL(neighbours[1]);

    freeCell(neighbour);
}

void Cell_Should_Not_Add_Neighbour_If_It_Has_No_Space_For_One()
{
    Cell* neighbour[10];

    for (int i = 0; i < 10; i++)
    {
        neighbour[i] = allocateCell();
        addCellNeighbour(cell, neighbour[i]);
    }

    for (int i = 0; i < 8; i++)
        TEST_ASSERT_EQUAL(neighbour[i], cellNeighbours(cell)[i]);

    for (int i = 0; i < 10; i++)
        freeCell(neighbour[i]);
}

void Cell_Should_Calculate_Its_Value_By_Checking_Neighbours_Bombs()
{
    Cell* c1 = allocateCell();
    setCellValue(c1, BOMB);

    Cell* c2 = allocateCell();
    setCellValue(c2, BOMB);

    addCellNeighbour(cell, c1);
    addCellNeighbour(cell, c2);

    calculateCellValue(cell);

    TEST_ASSERT_EQUAL(TWO, cellValue(cell));

    freeCell(c1);
    freeCell(c2);
}

void Cell_Should_Not_Sync_Its_Value_If_It_Is_Has_Bomb()
{
    setCellValue(cell, BOMB);

    calculateCellValue(cell);

    TEST_ASSERT_EQUAL_INT(BOMB, cellValue(cell));
}

void testCell()
{
    RUN_TEST(Cell_Allocation_Should_Return_Allocated_Cell);

    RUN_TEST(Allocated_Cell_Should_Not_Be_Opened_By_Default);
    RUN_TEST(Allocated_Cell_Should_Not_Be_Marked_By_Default);
    RUN_TEST(Allocated_Cell_Should_Have_Zero_Value_By_Default);
    RUN_TEST(Allocated_Cell_Should_Not_Have_Neighbours);

    RUN_TEST(Cell_Should_Add_Neighbour_To_Itself);
    RUN_TEST(Cell_Should_Not_Add_Same_Neighbour_More_Than_Once);
    RUN_TEST(Cell_Should_Not_Add_Neighbour_If_It_Has_No_Space_For_One);

    RUN_TEST(Cell_Should_Calculate_Its_Value_By_Checking_Neighbours_Bombs);
}