#include "sample.h"
#include "stdbool.h"
#include "unity.h"

void setUp() { }

void tearDown() { }

void Test_Sample()
{
    TEST_ASSERT_TRUE(sample());
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(Test_Sample);

    return UNITY_END();
}