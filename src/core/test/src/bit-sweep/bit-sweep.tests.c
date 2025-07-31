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

void testBitSweep()
{
    RUN_TEST(Bit_Sweep_Allocation_Should_Allocate_New_Bit_Sweep);
}
