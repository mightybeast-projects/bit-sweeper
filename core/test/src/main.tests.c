#include "bit-sweep.h"
#include "bit-sweep.tests.h"
#include "cell.tests.h"
#include "stdbool.h"
#include "unity.h"

void setUp()
{
    setUpCell();
    setUpBitSweep();
}

void tearDown()
{
    tearDownCell();
    tearDownBitSweep();
}

int main()
{
    UNITY_BEGIN();

    testCell();
    testBitSweep();

    return UNITY_END();
}