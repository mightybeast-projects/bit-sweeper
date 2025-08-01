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

void printTestBitSweep()
{
    BitSweep* game = allocateBitSweep();

    printBitSweep(game);

    freeBitSweep(game);
}

int main()
{
    UNITY_BEGIN();

    testCell();
    testBitSweep();

    printTestBitSweep();

    return UNITY_END();
}