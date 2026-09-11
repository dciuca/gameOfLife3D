// include/core/PatternLibrary.h
#pragma once

#include "Grid.h"

class PatternLibrary
{
public:
    // Pattern enum
    enum class Pattern
    {
        CHAOS_SPARSE,
        CHAOS_DENSE,
        GLIDER_BAYS
    };

    static void initChaos(Grid &grid, float density = 0.3f);
    static void initGlider3D_Bays(Grid &grid);

    // Dispatcher
    static void initPattern(Grid &grid, Pattern pattern);
    static const char *getPatternName(Pattern pattern);
};