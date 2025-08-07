#include "bit-sweep.h"
#include "bit-sweep.tests.h"
#include "cell.tests.h"
#include "stdbool.h"
#include "unity.h"

void setUp(void)
{
    setUpCell();
    setUpBitSweep();
}

void tearDown(void)
{
    tearDownCell();
    tearDownBitSweep();
}

int main(void)
{
    UNITY_BEGIN();

    testCell();
    testBitSweep();

    return UNITY_END();
}