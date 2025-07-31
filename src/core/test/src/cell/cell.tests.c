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

void runCellTests()
{
    RUN_TEST(Cell_Allocation_Should_Return_Allocated_Cell);

    RUN_TEST(Allocated_Cell_Should_Not_Be_Opened_By_Default);
    RUN_TEST(Allocated_Cell_Should_Not_Be_Marked_By_Default);
    RUN_TEST(Allocated_Cell_Should_Have_Zero_Value_By_Default);
    RUN_TEST(Allocated_Cell_Should_Not_Have_Neighbours);
}