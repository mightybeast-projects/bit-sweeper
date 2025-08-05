#include "bit-sweep.tests.h"
#include "bit-sweep.h"
#include "unity.h"

static unsigned int seed = 1;
static unsigned int width = 10;
static unsigned int height = 10;
static unsigned int bombCount = 15;

BitSweep* bitSweep;

void setUpBitSweep(void)
{
    BitSweepParams params = { seed, width, height, bombCount };

    bitSweep = allocateBitSweep(params);
}

void tearDownBitSweep(void)
{
    freeBitSweep(bitSweep);
}

void Bit_Sweep_Allocation_Should_Allocate_New_Bit_Sweep()
{
    TEST_ASSERT_NOT_NULL(bitSweep);

    printBitSweep(bitSweep);
}

void Bit_Sweep_Allocation_Should_Not_Allocate_New_Bit_Sweep_If_Bomb_Count_Is_Higher_Than_Cells_Count()
{
    BitSweepParams params = { seed, width, height, 200 };

    BitSweep* res = allocateBitSweep(params);

    TEST_ASSERT_NULL(res);

    freeBitSweep(res);
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

void Allocated_Bit_Sweep_Should_Have_Zero_Opened_Cells()
{
    TEST_ASSERT_EQUAL_INT(0, bitSweepOpenedCellsCount(bitSweep));
}

void Allocated_Bit_Sweep_Should_Have_Initialized_Cells()
{
    TEST_ASSERT_NOT_NULL(bitSweepCells(bitSweep));
};

void Allocated_Bit_Sweep_Should_Have_Initialized_Cells_Indexes()
{
    Cell*** cells = bitSweepCells(bitSweep);

    for (int i = 0; i < bitSweepWidth(bitSweep); i++)
    {
        for (int j = 0; j < bitSweepHeight(bitSweep); j++)
        {
            Cell* cell = cells[i][j];

            TEST_ASSERT_EQUAL_UINT(i, cellI(cell));
            TEST_ASSERT_EQUAL_UINT(j, cellJ(cell));
        }
    }
}

void Allocated_Bit_Sweep_Should_Have_Randomized_Bomb_Cells()
{
    int bombCount = 0;

    Cell*** cells = bitSweepCells(bitSweep);

    for (int i = 0; i < bitSweepWidth(bitSweep); i++)
        for (int j = 0; j < bitSweepHeight(bitSweep); j++)
            if (cellContainsBomb(cells[i][j]))
                bombCount++;

    TEST_ASSERT_EQUAL_UINT(bitSweepBombCount(bitSweep), bombCount);
}

void Allocated_Bit_Sweep_Should_Have_Some_Cells_With_Non_Zero_Values()
{
    bool nonZeroValue = false;

    Cell*** cells = bitSweepCells(bitSweep);

    for (int i = 0; i < bitSweepWidth(bitSweep); i++)
    {
        for (int j = 0; j < bitSweepHeight(bitSweep); j++)
        {
            Cell* cell = cells[i][j];

            if (cellValue(cell) != ZERO && !cellContainsBomb(cell))
                nonZeroValue = true;
        }
    }

    TEST_ASSERT_TRUE(nonZeroValue);
}

void Allocated_Bit_Sweep_Should_Have_Non_Bomb_Cells_Count_Equal_To_All_Cells_Minus_Bomb_Count()
{
    TEST_ASSERT_EQUAL_INT(85, bitSweepNonBombCellsCount(bitSweep));
}

void Bit_Sweep_Should_Return_Opened_Cell_After_Opening_One()
{
    Cell* openedCell = openCellAt(bitSweep, 0, 0);

    TEST_ASSERT_NOT_NULL(openedCell);
    TEST_ASSERT_EQUAL(bitSweepCells(bitSweep)[0][0], openedCell);
}

void Bit_Sweep_Should_Open_Cell_At_Position()
{
    Cell* openedCell = openCellAt(bitSweep, 4, 5);

    TEST_ASSERT_TRUE(cellIsOpened(openedCell));
}

void Bit_Sweep_Should_Not_Open_Marked_Cell()
{
    Cell* cell = bitSweepCells(bitSweep)[5][5];

    toggleCellMark(cell);

    Cell* res = openCellAt(bitSweep, 5, 5);

    TEST_ASSERT_FALSE(cellIsOpened(cell));
    TEST_ASSERT_EQUAL(res, cell);

    printBitSweep(bitSweep);
}

void Bit_Sweep_Should_Open_Only_Selected_Cell_If_It_Has_Bomb()
{
    openCellAt(bitSweep, 2, 1);

    Cell*** cells = bitSweepCells(bitSweep);

    TEST_ASSERT_FALSE(cellIsOpened(cells[2][0]));
    TEST_ASSERT_FALSE(cellIsOpened(cells[2][2]));
    TEST_ASSERT_FALSE(cellIsOpened(cells[1][0]));
    TEST_ASSERT_FALSE(cellIsOpened(cells[1][2]));

    printBitSweep(bitSweep);
}

void Bit_Sweep_Should_Open_Only_Selected_Cell_If_It_Has_Non_Zero_Value()
{
    Cell* openedCell = openCellAt(bitSweep, 1, 0);
    Cell*** cells = bitSweepCells(bitSweep);

    TEST_ASSERT_FALSE(cellIsOpened(cells[0][0]));
    TEST_ASSERT_EQUAL(openedCell, bitSweepCells(bitSweep)[1][0]);

    printBitSweep(bitSweep);
}

void Bit_Sweep_Should_Recursively_Open_All_Neighbour_Cells_That_Have_Zero_Value_If_Selected_Cell_Has_Zero_Value()
{
    openCellAt(bitSweep, 0, 7);

    Cell*** cells = bitSweepCells(bitSweep);

    TEST_ASSERT_TRUE(cellIsOpened(cells[0][8]));
    TEST_ASSERT_TRUE(cellIsOpened(cells[0][9]));

    printBitSweep(bitSweep);
}

void Bit_Sweep_Should_Recursively_Open_All_Neighbour_Cells_That_Have_Non_Bomb_Value_If_Selected_Cell_Has_Zero_Value()
{
    openCellAt(bitSweep, 0, 7);

    Cell*** cells = bitSweepCells(bitSweep);

    TEST_ASSERT_TRUE(cellIsOpened(cells[0][6]));
    TEST_ASSERT_TRUE(cellIsOpened(cells[1][6]));
    TEST_ASSERT_TRUE(cellIsOpened(cells[1][7]));

    printBitSweep(bitSweep);
}

void Bit_Sweep_Should_Add_To_Opened_Cells_Count_On_Cell_Open()
{
    openCellAt(bitSweep, 0, 7);

    TEST_ASSERT_EQUAL_INT(12, bitSweep->openedCellsCount);
}

void Bit_Sweep_Should_Finish_Itself_If_All_Non_Bomb_Cells_Are_Opened()
{
    BitSweepParams params = { 1, 2, 2, 1 };

    BitSweep* game = allocateBitSweep(params);

    openCellAt(game, 0, 0);
    openCellAt(game, 0, 1);
    openCellAt(game, 1, 0);

    printBitSweep(game);

    TEST_ASSERT_TRUE(game->isFinished);

    freeBitSweep(game);
}

void Bit_Sweep_Should_Finish_Itself_If_Bomb_Cell_Was_Opened()
{
    Cell* res = openCellAt(bitSweep, 2, 1);

    TEST_ASSERT_TRUE(bitSweepIsFinished(bitSweep));
    TEST_ASSERT_EQUAL(res, bitSweepCells(bitSweep)[2][1]);

    printBitSweep(bitSweep);
}

void Bit_Sweep_Should_Not_Open_Cell_If_Game_Is_Finished()
{
    openCellAt(bitSweep, 2, 1);

    const Cell* res = openCellAt(bitSweep, 0, 0);

    TEST_ASSERT_NULL(res);

    printBitSweep(bitSweep);
}

void testBitSweep(void)
{
    RUN_TEST(Bit_Sweep_Allocation_Should_Allocate_New_Bit_Sweep);
    RUN_TEST(Bit_Sweep_Allocation_Should_Not_Allocate_New_Bit_Sweep_If_Bomb_Count_Is_Higher_Than_Cells_Count);

    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Initialized_Width);
    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Initialized_Height);
    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Initialized_Cells_Indexes);
    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Initialized_Bomb_Count);
    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Zero_Opened_Cells);
    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Non_Bomb_Cells_Count_Equal_To_All_Cells_Minus_Bomb_Count);
    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Initialized_Cells);
    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Randomized_Bomb_Cells);
    RUN_TEST(Allocated_Bit_Sweep_Should_Have_Some_Cells_With_Non_Zero_Values);

    RUN_TEST(Bit_Sweep_Should_Return_Opened_Cell_After_Opening_One);
    RUN_TEST(Bit_Sweep_Should_Open_Cell_At_Position);
    RUN_TEST(Bit_Sweep_Should_Not_Open_Marked_Cell);
    RUN_TEST(Bit_Sweep_Should_Open_Only_Selected_Cell_If_It_Has_Bomb);
    RUN_TEST(Bit_Sweep_Should_Open_Only_Selected_Cell_If_It_Has_Non_Zero_Value);
    RUN_TEST(Bit_Sweep_Should_Recursively_Open_All_Neighbour_Cells_That_Have_Zero_Value_If_Selected_Cell_Has_Zero_Value);
    RUN_TEST(Bit_Sweep_Should_Recursively_Open_All_Neighbour_Cells_That_Have_Non_Bomb_Value_If_Selected_Cell_Has_Zero_Value);
    RUN_TEST(Bit_Sweep_Should_Add_To_Opened_Cells_Count_On_Cell_Open);
    RUN_TEST(Bit_Sweep_Should_Finish_Itself_If_All_Non_Bomb_Cells_Are_Opened);
    RUN_TEST(Bit_Sweep_Should_Finish_Itself_If_Bomb_Cell_Was_Opened);
    RUN_TEST(Bit_Sweep_Should_Not_Open_Cell_If_Game_Is_Finished);
}
