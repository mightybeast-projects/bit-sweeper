#include "widget.tests.h"
#include "unity.h"
#include "widget.h"

void Test_Widget_Draw()
{
    TEST_ASSERT_TRUE(draw());
}

void testWidget()
{
    RUN_TEST(Test_Widget_Draw);
}