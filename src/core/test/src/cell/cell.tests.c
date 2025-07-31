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
    TEST_ASSERT_FALSE(cell->isOpened);
}

void Allocated_Cell_Should_Not_Be_Marked_By_Default()
{
    TEST_ASSERT_FALSE(cell->isMarked);
}

void Allocated_Cell_Should_Have_Zero_Value_By_Default()
{
    TEST_ASSERT_EQUAL_INT(ZERO, cell->value);
}

void Allocated_Cell_Should_Not_Have_Neighbours()
{
    TEST_ASSERT_NOT_NULL(cell->neighbours);

    for (int i = 0; i < sizeof(cell->neighbours); i++)
        TEST_ASSERT_NULL(cell->neighbours[i]);
}

void Cell_Should_Add_Neighbour_To_Itself()
{
    Cell* neighbour = allocateCell();

    addNeighbour(cell, neighbour);

    TEST_ASSERT_NOT_NULL(cell->neighbours[0]);

    freeCell(neighbour);
}

void Cell_Should_Not_Add_Same_Neighbour_More_Than_Once()
{
    Cell* neighbour = allocateCell();

    addNeighbour(cell, neighbour);
    addNeighbour(cell, neighbour);

    TEST_ASSERT_NOT_NULL(cell->neighbours[0]);
    TEST_ASSERT_NULL(cell->neighbours[1]);

    freeCell(neighbour);
}

void Cell_Should_Not_Add_Neighbour_If_It_Has_No_Space_For_One()
{
    Cell* neighbour[10];

    for (int i = 0; i < 10; i++)
    {
        neighbour[i] = allocateCell();
        addNeighbour(cell, neighbour[i]);
    }

    for (int i = 0; i < 8; i++)
        TEST_ASSERT_EQUAL(neighbour[i], cell->neighbours[i]);

    for (int i = 0; i < 10; i++)
        freeCell(neighbour[i]);
}

void runCellTests()
{
    RUN_TEST(Cell_Allocation_Should_Return_Allocated_Cell);

    RUN_TEST(Allocated_Cell_Should_Not_Be_Opened_By_Default);
    RUN_TEST(Allocated_Cell_Should_Not_Be_Marked_By_Default);
    RUN_TEST(Allocated_Cell_Should_Have_Zero_Value_By_Default);
    RUN_TEST(Allocated_Cell_Should_Not_Have_Neighbours);

    RUN_TEST(Cell_Should_Add_Neighbour_To_Itself);
    RUN_TEST(Cell_Should_Not_Add_Same_Neighbour_More_Than_Once);
    RUN_TEST(Cell_Should_Not_Add_Neighbour_If_It_Has_No_Space_For_One);
}