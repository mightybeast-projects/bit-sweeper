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
    TEST_ASSERT_NOT_NULL(cell->neighbours);
}

void runCellTests()
{
    RUN_TEST(Cell_Allocation_Should_Return_Allocated_Cell);
}