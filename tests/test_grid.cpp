// tests/test_grid.cpp

#include <gtest/gtest.h>
#include "core/Grid.h"
#include <algorithm>
#include <set>

// ============================================================
// TEST CASE 1: Construction and dimensions
// ============================================================

TEST(GridTest, CanBeCreatedWithCorrectDimensions)
{
    Grid grid(10, 15, 20);

    EXPECT_EQ(grid.getWidth(), 10);
    EXPECT_EQ(grid.getHeight(), 15);
    EXPECT_EQ(grid.getDepth(), 20);
    EXPECT_EQ(grid.getTotalCells(), 10 * 15 * 20);
}

TEST(GridTest, DifferentDimensionsWorkCorrectly)
{
    Grid small(2, 3, 4);
    EXPECT_EQ(small.getTotalCells(), 24);

    Grid large(100, 100, 100);
    EXPECT_EQ(large.getTotalCells(), 1000000);
}

// ============================================================
// TEST CASE 2: Initialization and reset
// ============================================================

TEST(GridTest, CellsAreInitiallyZero)
{
    Grid grid(5, 5, 5);

    for (size_t z = 0; z < 5; z++)
    {
        for (size_t y = 0; y < 5; y++)
        {
            for (size_t x = 0; x < 5; x++)
            {
                EXPECT_EQ(grid.getCellByPosition(x, y, z), 0);
            }
        }
    }
}

TEST(GridTest, ResetGridSetsAllCellsToZero)
{
    Grid grid(3, 3, 3);

    // Set some cells
    grid.getGridData()[0] = 1;
    grid.getGridData()[1] = 1;
    grid.getGridData()[5] = 1;

    grid.resetGrid();

    for (size_t i = 0; i < grid.getTotalCells(); i++)
    {
        EXPECT_EQ(grid.getGridData()[i], 0);
    }
}

// ============================================================
// TEST CASE 3: Cell access
// ============================================================

TEST(GridTest, GetCellByPositionWorksCorrectly)
{
    Grid grid(5, 5, 5);

    // Test some positions
    grid.getGridData()[0] = 1;  // (0,0,0)
    grid.getGridData()[12] = 1; // (2,2,0) with width=5, height=5
    grid.getGridData()[62] = 1; // (2,2,2) with width=5, height=5

    EXPECT_EQ(grid.getCellByPosition(0, 0, 0), 1);
    EXPECT_EQ(grid.getCellByPosition(2, 2, 0), 1);
    EXPECT_EQ(grid.getCellByPosition(2, 2, 2), 1);

    // Verify that other cells are zero
    EXPECT_EQ(grid.getCellByPosition(1, 0, 0), 0);
    EXPECT_EQ(grid.getCellByPosition(0, 1, 0), 0);
    EXPECT_EQ(grid.getCellByPosition(0, 0, 1), 0);
}

TEST(GridTest, DirectDataAccessMatchesGetCellByPosition)
{
    Grid grid(3, 3, 3);
    auto &data = grid.getGridData();

    // Set some cells via direct index
    data[0] = 1;  // (0,0,0)
    data[4] = 1;  // (1,1,0) with width=3, height=3
    data[13] = 1; // (1,1,1) with width=3, height=3

    EXPECT_EQ(grid.getCellByPosition(0, 0, 0), 1);
    EXPECT_EQ(grid.getCellByPosition(1, 1, 0), 1);
    EXPECT_EQ(grid.getCellByPosition(1, 1, 1), 1);
}

// ============================================================
// TEST CASE 4: Offsets
// ============================================================

TEST(GridTest, OffsetsArrayHasExactly26Entries)
{
    Grid grid(10, 10, 10);
    const auto &offsets = grid.getOffsets();

    EXPECT_EQ(offsets.size(), 26);
}

TEST(GridTest, OffsetsDoNotContainZero)
{
    Grid grid(10, 10, 10);
    const auto &offsets = grid.getOffsets();

    EXPECT_EQ(std::find(offsets.begin(), offsets.end(), 0), offsets.end());
}

TEST(GridTest, OffsetsAreSymmetric)
{
    Grid grid(10, 10, 10);
    const auto &offsets = grid.getOffsets();

    std::set<int> offsetSet(offsets.begin(), offsets.end());

    // For each offset, the opposite must be present
    for (int offset : offsets)
    {
        EXPECT_NE(offsetSet.find(-offset), offsetSet.end());
    }
}

TEST(GridTest, OffsetsAreCorrectForKnownGridSize)
{
    Grid grid(5, 5, 5); // width=5, height=5
    const auto &offsets = grid.getOffsets();

    // For width=5, height=5:
    // - Shift in X: ±1
    // - Shift in Y: ±5 (width)
    // - Shift in Z: ±25 (width * height)

    // Look for known offsets
    EXPECT_NE(std::find(offsets.begin(), offsets.end(), 1), offsets.end());   // dx=+1
    EXPECT_NE(std::find(offsets.begin(), offsets.end(), -1), offsets.end());  // dx=-1
    EXPECT_NE(std::find(offsets.begin(), offsets.end(), 5), offsets.end());   // dy=+1
    EXPECT_NE(std::find(offsets.begin(), offsets.end(), -5), offsets.end());  // dy=-1
    EXPECT_NE(std::find(offsets.begin(), offsets.end(), 25), offsets.end());  // dz=+1
    EXPECT_NE(std::find(offsets.begin(), offsets.end(), -25), offsets.end()); // dz=-1

    // Extreme diagonal: dx=+1, dy=+1, dz=+1 → 1 + 5 + 25 = 31
    EXPECT_NE(std::find(offsets.begin(), offsets.end(), 31), offsets.end());

    // Opposite extreme diagonal: dx=-1, dy=-1, dz=-1 → -1 - 5 - 25 = -31
    EXPECT_NE(std::find(offsets.begin(), offsets.end(), -31), offsets.end());
}

TEST(GridTest, OffsetsAreIdenticalForDifferentGridInstancesWithSameSize)
{
    Grid grid1(10, 10, 10);
    Grid grid2(10, 10, 10);

    const auto &offsets1 = grid1.getOffsets();
    const auto &offsets2 = grid2.getOffsets();

    for (size_t i = 0; i < 26; i++)
    {
        EXPECT_EQ(offsets1[i], offsets2[i]);
    }
}

// ============================================================
// TEST CASE 5: Memory management (ghost border)
// ============================================================

TEST(GridTest, GridStoresDataContiguously)
{
    Grid grid(4, 4, 4);
    auto &data = grid.getGridData();

    // Verify that data is contiguous
    size_t total = grid.getTotalCells();
    EXPECT_EQ(data.size(), total);

    // Verify that allocation is contiguous (consecutive addresses)
    for (size_t i = 0; i < total - 1; i++)
    {
        EXPECT_EQ(&data[i] + 1, &data[i + 1]);
    }
}

TEST(GridTest, CellPositionsMapCorrectlyToFlatIndices)
{
    Grid grid(3, 4, 5);
    auto &data = grid.getGridData();

    // width=3, height=4
    // (x, y, z) → (z * height + y) * width + x

    // Test coordinate (0,0,0) → index 0
    EXPECT_EQ(grid.getCellByPosition(0, 0, 0), data[0]);

    // Test coordinate (2,0,0) → index 2
    grid.getGridData()[2] = 1;
    EXPECT_EQ(grid.getCellByPosition(2, 0, 0), 1);

    // Test coordinate (0,3,0) → (0 * 4 + 3) * 3 + 0 = 9
    grid.getGridData()[9] = 1;
    EXPECT_EQ(grid.getCellByPosition(0, 3, 0), 1);

    // Test coordinate (0,0,4) → (4 * 4 + 0) * 3 + 0 = 48
    grid.getGridData()[48] = 1;
    EXPECT_EQ(grid.getCellByPosition(0, 0, 4), 1);
}

// ============================================================
// TEST CASE 6: Edge cases
// ============================================================

TEST(GridTest, GridWithSize1x1x1WorksCorrectly)
{
    Grid grid(1, 1, 1);

    EXPECT_EQ(grid.getTotalCells(), 1);
    EXPECT_EQ(grid.getCellByPosition(0, 0, 0), 0);

    grid.getGridData()[0] = 1;
    EXPECT_EQ(grid.getCellByPosition(0, 0, 0), 1);

    grid.resetGrid();
    EXPECT_EQ(grid.getCellByPosition(0, 0, 0), 0);
}

TEST(GridTest, GridWithSize0IsHandledCorrectly)
{
    Grid grid(0, 0, 0);

    EXPECT_EQ(grid.getTotalCells(), 0);
    EXPECT_TRUE(grid.getGridData().empty());
}

TEST(GridTest, MultipleResetOperationsWorkCorrectly)
{
    Grid grid(3, 3, 3);

    // First operation
    grid.getGridData()[0] = 1;
    grid.getGridData()[1] = 1;
    grid.resetGrid();

    for (size_t i = 0; i < 9; i++)
    {
        EXPECT_EQ(grid.getGridData()[i], 0);
    }

    // Second operation
    grid.getGridData()[4] = 1;
    grid.getGridData()[8] = 1;
    grid.resetGrid();

    for (size_t i = 0; i < 9; i++)
    {
        EXPECT_EQ(grid.getGridData()[i], 0);
    }
}

// ============================================================
// TEST CASE 7: Performance and consistency
// ============================================================

TEST(GridTest, AllCellsAreAccessibleAfterGridCreation)
{
    Grid grid(10, 10, 10);
    auto &data = grid.getGridData();

    // Set all cells to 1
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i] = 1;
    }

    // Verify that all cells are 1
    for (size_t z = 0; z < 10; z++)
    {
        for (size_t y = 0; y < 10; y++)
        {
            for (size_t x = 0; x < 10; x++)
            {
                EXPECT_EQ(grid.getCellByPosition(x, y, z), 1);
            }
        }
    }

    // Reset and verify all are 0
    grid.resetGrid();
    for (size_t i = 0; i < data.size(); i++)
    {
        EXPECT_EQ(data[i], 0);
    }
}

// ============================================================
// TEST CASE 8: getGridData reference
// ============================================================

TEST(GridTest, GetGridDataReturnsModifiableReference)
{
    Grid grid(5, 5, 5);

    // Modify via reference
    auto &data = grid.getGridData();
    data[0] = 42;
    data[10] = 99;

    // Verify that modifications are visible
    EXPECT_EQ(grid.getCellByPosition(0, 0, 0), 42);
    EXPECT_EQ(grid.getCellByPosition(0, 2, 0), 99); // (10 / 5 = 2, 10 % 5 = 0)

    // Verify that the reference points to the same vector
    EXPECT_EQ(&data, &grid.getGridData());
}

// ============================================================
// TEST CASE 9: Const correctness
// ============================================================

TEST(GridTest, GridCanBeUsedInConstContext)
{
    Grid grid(3, 3, 3);
    grid.getGridData()[0] = 1;

    const Grid &constGrid = grid;

    // Const methods must work
    EXPECT_EQ(constGrid.getWidth(), 3);
    EXPECT_EQ(constGrid.getHeight(), 3);
    EXPECT_EQ(constGrid.getDepth(), 3);
    EXPECT_EQ(constGrid.getTotalCells(), 27);
    EXPECT_EQ(constGrid.getCellByPosition(0, 0, 0), 1);
    EXPECT_EQ(constGrid.getOffsets().size(), 26);

    // getGridData() is not const, so it cannot be called on constGrid
    // (this is correct - compilation would fail if attempted)
}

// ============================================================
// TEST CASE 10: GUARD_CELL constant
// ============================================================

TEST(GridTest, GuardCellConstantIsDefinedCorrectly)
{
    EXPECT_EQ(Grid::GUARD_CELL, 1);
}

// ============================================================
// TEST CASE 11: Multiple grid instances
// ============================================================

TEST(GridTest, MultipleGridInstancesAreIndependent)
{
    Grid grid1(3, 3, 3);
    Grid grid2(3, 3, 3);

    grid1.getGridData()[0] = 1;
    grid2.getGridData()[3] = 1;

    EXPECT_EQ(grid1.getCellByPosition(0, 0, 0), 1);
    EXPECT_EQ(grid1.getCellByPosition(0, 1, 0), 0);

    EXPECT_EQ(grid2.getCellByPosition(0, 1, 0), 1);
    EXPECT_EQ(grid2.getCellByPosition(0, 0, 0), 0);
}

// ============================================================
// TEST CASE 12: Toroidal guard cells
// ============================================================

TEST(GridTest, GuardCellsMirrorOppositeFacesOnLargeAxes)
{
    Grid grid(5, 5, 5); // logical 3x3x3 on every axis -> all axes wrap

    grid.setCellByPosition(3, 2, 2, 1); // last interior x
    grid.updateGuardCells();

    EXPECT_EQ(grid.getCellByPosition(0, 2, 2), 1); // left guard mirrors x=3
    EXPECT_EQ(grid.getCellByPosition(4, 2, 2), 0); // right guard mirrors x=1
}

TEST(GridTest, GuardCellsWrapEdgesAndCorners)
{
    Grid grid(5, 5, 5);

    grid.setCellByPosition(1, 1, 1, 1); // interior corner
    grid.updateGuardCells();

    // The opposite corner guard (and edge/face guards) must see it
    EXPECT_EQ(grid.getCellByPosition(4, 4, 4), 1);
    EXPECT_EQ(grid.getCellByPosition(4, 4, 1), 1);
    EXPECT_EQ(grid.getCellByPosition(4, 1, 4), 1);
    EXPECT_EQ(grid.getCellByPosition(1, 4, 4), 1);
    EXPECT_EQ(grid.getCellByPosition(0, 0, 0), 0);
}

TEST(GridTest, GuardCellsStayDeadOnAxesWithTwoLogicalLayers)
{
    Grid grid(5, 4, 5); // logical height 2: wrapping Y would double count

    grid.setCellByPosition(2, 1, 2, 1);
    grid.setCellByPosition(2, 2, 2, 1);
    grid.getGridData()[0] = 1; // stale guard value must be cleared
    grid.updateGuardCells();

    EXPECT_EQ(grid.getCellByPosition(2, 0, 2), 0);
    EXPECT_EQ(grid.getCellByPosition(2, 3, 2), 0);
    EXPECT_EQ(grid.getCellByPosition(0, 0, 0), 0);
}

TEST(GridTest, SingleLayerGridCountsEachNeighbourOnce)
{
    Grid grid(5, 3, 5); // logical height 1 (2D game on a torus)

    // Only live cell: interior corner (1,1,1). Its torus neighbours in the
    // (x,z) plane are 8 distinct cells, one of which wraps to (3,1,3).
    grid.setCellByPosition(3, 1, 3, 1);
    grid.updateGuardCells();

    const auto &data = grid.getGridDataReadOnly();
    const size_t idx = 1 + 1 * 5 + 1 * 5 * 3;
    int neighbours = 0;
    for (int offset : grid.getOffsets())
        neighbours += data[idx + offset];

    EXPECT_EQ(neighbours, 1);
}

// ============================================================
// TEST CASE 13: Logical vs physical dimensions (concept test)
// ============================================================

TEST(GridTest, GridDimensionsAreConsistentWithTotalCells)
{
    Grid grid(7, 11, 13);

    // Logical dimensions are those passed to the constructor
    EXPECT_EQ(grid.getWidth(), 7);
    EXPECT_EQ(grid.getHeight(), 11);
    EXPECT_EQ(grid.getDepth(), 13);

    // Total cells is width * height * depth
    EXPECT_EQ(grid.getTotalCells(), 7 * 11 * 13);
}