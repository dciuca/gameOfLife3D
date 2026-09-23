// src/core/PatternLibrary.cpp
#include "core/PatternLibrary.h"
#include "utils/Utils.h"
#include <random>
#include <cmath>

// ============================================================
// PATTERN 1: CHAOS
// ============================================================
void PatternLibrary::initChaos(Grid &grid, float density)
{
    grid.resetGrid();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    const size_t w = grid.getWidth();
    const size_t h = grid.getHeight();
    const size_t d = grid.getDepth();

    for (size_t z = 0; z < d; z++)
    {
        for (size_t y = 0; y < h; y++)
        {
            for (size_t x = 0; x < w; x++)
            {
                if (dist(gen) < density)
                {
                    grid.setCellByPosition(x, y, z, 1);
                }
            }
        }
    }
}

// ============================================================
// PATTERN 2: GLIDER 3D Bays
// ============================================================
void PatternLibrary::initGlider3D_Bays(Grid &grid)
{
    grid.resetGrid();
    const int cx = grid.getWidth() / 2;
    const int cy = grid.getHeight() / 2;
    const int cz = grid.getDepth() / 2;

    // Pattern Glider 2D classic duplicated
    // . O .
    // . . O
    // O O O

    // Layer Z = 0
    grid.setCellByPosition(cx, cy, cz, 1);
    grid.setCellByPosition(cx + 1, cy + 1, cz, 1);
    grid.setCellByPosition(cx, cy + 2, cz, 1);
    grid.setCellByPosition(cx + 1, cy + 2, cz, 1);
    grid.setCellByPosition(cx + 2, cy + 2, cz, 1);

    // Layer Z = 1
    grid.setCellByPosition(cx, cy, cz + 1, 1);
    grid.setCellByPosition(cx + 1, cy + 1, cz + 1, 1);
    grid.setCellByPosition(cx, cy + 2, cz + 1, 1);
    grid.setCellByPosition(cx + 1, cy + 2, cz + 1, 1);
    grid.setCellByPosition(cx + 2, cy + 2, cz + 1, 1);
}

// ============================================================
// PATTERN DISPATCHER
// ============================================================
void PatternLibrary::initPattern(Grid &grid, Pattern pattern)
{
    switch (pattern)
    {
    case Pattern::CHAOS_SPARSE:
        initChaos(grid, 0.15f);
        break;
    case Pattern::CHAOS_DENSE:
        initChaos(grid, 0.30f);
        break;
    case Pattern::GLIDER_BAYS:
        initGlider3D_Bays(grid);
        break;
    }
}

// ============================================================
// PATTERN NAME LOOKUP
// ============================================================
const char *PatternLibrary::getPatternName(Pattern pattern)
{
    switch (pattern)
    {
    case Pattern::CHAOS_SPARSE:
        return "Chaos (15%)";
    case Pattern::CHAOS_DENSE:
        return "Chaos (30%)";
    case Pattern::GLIDER_BAYS:
        return "Glider 3D";
    default:
        return "Unknown";
    }
}