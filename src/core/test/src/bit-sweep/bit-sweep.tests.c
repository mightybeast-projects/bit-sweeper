#include "bit-sweep.tests.h"
#include "bit-sweep.h"
#include "unity.h"

BitSweep* bitSweep;

void setUpBitSweep()
{
    bitSweep = allocateBitSweep();
}

void tearDownBitSweep()
{
    freeBitSweep(bitSweep);
}

void Bit_Sweep_Allocation_Should_Allocate_New_Bit_Sweep()
{
    TEST_ASSERT_NOT_NULL(bitSweep);
}

void Allocated_Bit_Sweep_Should_Have_Initialized_Width()
{
    TEST_ASSERT_EQUAL_INT(10, bitSweepWidth(bitSweep));
};

void Allocated_Bit_Sweep_Should_Have_Initialized_Height()
{
    TEST_ASSERT_EQUAL_INT(10, bitSweepHeight(bitSweep));
};

void Allocated_Bit_Sweep_Should_Have_Initialized_Bomb_Count()
{
    TEST_ASSERT_EQUAL_INT(10, bitSweepBombCount(bitSweep));
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

void testBitSweep()
{
    RUN_TEST(Bit_Sweep_Allocation_Should_Allocate_New_Bit_Sweep);

    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Initialized_Width);
    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Initialized_Height);
    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Initialized_Bomb_Count);
    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Initialized_Cells);

    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Randomized_Bomb_Cells);
    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Some_Cells_With_Non_Zero_Values);
}
