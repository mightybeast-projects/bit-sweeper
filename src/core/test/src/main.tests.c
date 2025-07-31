#include "cell.tests.h"
#include "stdbool.h"
#include "unity.h"

void setUp()
{
    setUpCell();
}

void tearDown()
{
    tearDownCell();
}

int main()
{
    UNITY_BEGIN();

    runCellTests();

    return UNITY_END();
}