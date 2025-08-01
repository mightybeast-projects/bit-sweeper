#include "bit-sweep.tests.h"
#include "bit-sweep.h"
#include "unity.h"

static unsigned int seed = 1;
static unsigned int width = 10;
static unsigned int height = 10;
static unsigned int bombCount = 10;

BitSweep* bitSweep;

void setUpBitSweep()
{
    BitSweepParams params = { seed, width, height, bombCount };

    bitSweep = allocateBitSweep(params);
}

void tearDownBitSweep()
{
    freeBitSweep(bitSweep);
}

void Bit_Sweep_Allocation_Should_Allocate_New_Bit_Sweep()
{
    TEST_ASSERT_NOT_NULL(bitSweep);

    printBitSweep(bitSweep);
}

void Allocated_Bit_Sweep_Should_Have_Initialized_Width()
{
    TEST_ASSERT_EQUAL_UINT(width, bitSweepWidth(bitSweep));
};

void Allocated_Bit_Sweep_Should_Have_Initialized_Height()
{
    TEST_ASSERT_EQUAL_UINT(height, bitSweepHeight(bitSweep));
};

void Allocated_Bit_Sweep_Should_Have_Initialized_Bomb_Count()
{
    TEST_ASSERT_EQUAL_UINT(bombCount, bitSweepBombCount(bitSweep));
};

void Allocated_Bit_Sweep_Should_Have_Initialized_Cells()
{
    TEST_ASSERT_NOT_NULL(bitSweepCells(bitSweep));
};

void Allocated_Bit_Sweep_Should_Have_Randomized_Bomb_Cells()
{
    int bombCount = 0;

    Cell*** cells = bitSweepCells(bitSweep);

    for (int i = 0; i < bitSweepWidth(bitSweep); i++)
        for (int j = 0; j < bitSweepHeight(bitSweep); j++)
            if (cellValue(cells[i][j]) == BOMB)
                bombCount++;

    TEST_ASSERT_EQUAL_INT(bitSweepBombCount(bitSweep), bombCount);
}

void Allocated_Bit_Sweep_Should_Have_Some_Cells_With_Non_Zero_Values()
{
    bool nonZeroValue = false;

    Cell*** cells = bitSweepCells(bitSweep);

    for (int i = 0; i < bitSweepWidth(bitSweep); i++)
        for (int j = 0; j < bitSweepHeight(bitSweep); j++)
            if (cellValue(cells[i][j]) != ZERO
                && cellValue(cells[i][j]) != BOMB)
                nonZeroValue = true;

    TEST_ASSERT_TRUE(nonZeroValue);
}

void Bit_Sweep_Should_Return_Opened_Cell_After_Opening()
{
    Cell* openedCell = openCellAt(bitSweep, 2, 1);

    TEST_ASSERT_NOT_NULL(openedCell);
    TEST_ASSERT_EQUAL(bitSweepCells(bitSweep)[2][1], openedCell);
}

void On_Bit_Sweep_Cell_Open_Should_Open_Cell_At_Position()
{
    openCellAt(bitSweep, 4, 5);

    Cell*** cells = bitSweepCells(bitSweep);

    TEST_ASSERT_TRUE(cellIsOpened(cells[4][5]));
}

void testBitSweep()
{
    RUN_TEST(Bit_Sweep_Allocation_Should_Allocate_New_Bit_Sweep);

    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Initialized_Width);
    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Initialized_Height);
    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Initialized_Bomb_Count);
    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Initialized_Cells);

    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Randomized_Bomb_Cells);
    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Some_Cells_With_Non_Zero_Values);

    RUN_TEST(Bit_Sweep_Should_Return_Opened_Cell_After_Opening);
    RUN_TEST(On_Bit_Sweep_Cell_Open_Should_Open_Cell_At_Position);
}
