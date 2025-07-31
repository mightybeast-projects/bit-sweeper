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
    TEST_ASSERT_EQUAL_INT(10, bitSweep->width);
};

void Allocated_Bit_Sweep_Should_Have_Initialized_Height()
{
    TEST_ASSERT_EQUAL_INT(10, bitSweep->height);
};

void Allocated_Bit_Sweep_Should_Have_Initialized_Bomb_Count()
{
    TEST_ASSERT_EQUAL_INT(10, bitSweep->bombCount);
};

void Allocated_Bit_Sweep_Should_Have_Initialized_Cells()
{
    TEST_ASSERT_NOT_NULL(bitSweep->cells);
};

void Allocated_Bit_Sweep_Should_Have_Randomized_Bomb_Cells()
{
    int bombCount = 0;

    for (int i = 0; i < bitSweep->width; i++)
        for (int j = 0; j < bitSweep->height; j++)
            if (bitSweep->cells[i][j]->value == BOMB)
                bombCount++;

    TEST_ASSERT_EQUAL_INT(bitSweep->bombCount, bombCount);
}

void Allocated_Bit_Sweep_Should_Have_Some_Cells_With_Non_Zero_Values()
{
    bool nonZeroValue = false;

    for (int i = 0; i < bitSweep->width; i++)
        for (int j = 0; j < bitSweep->height; j++)
            if (bitSweep->cells[i][j]->value != ZERO
                && bitSweep->cells[i][j]->value != BOMB)
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
