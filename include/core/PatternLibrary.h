// include/core/PatternLibrary.h
#pragma once

#include "Grid.h"

class PatternLibrary
{
public:
    // Pattern enum
    enum class Pattern
    {
        BLINKER_3D,
        GLIDER_3D,
        GLIDER_3D_THICK,
        PULSAR_3D,
        CUBE_3X3X3,
        HOLLOW_CUBE,
        SPHERE,
        HOLLOW_SPHERE,
        CROSS_3D,
        ACORN,
        DOUBLE_BLINKER,
        BLINKER_PLANE,
        CHAOS,
        CHAOS_DENSE,
        CHAOS_SPARSE,
        EMPTY
    };

    static void initBlinker3D(Grid &grid);
    static void initGlider3D(Grid &grid);
    static void initGlider3D_Thick(Grid &grid);
    static void initPulsar3D(Grid &grid);
    static void initCube3x3x3(Grid &grid);
    static void initHollowCube(Grid &grid);
    static void initSphere(Grid &grid);
    static void initHollowSphere(Grid &grid);
    static void initCross3D(Grid &grid);
    static void initAcorn(Grid &grid);
    static void initDoubleBlinker(Grid &grid);
    static void initBlinkerPlane(Grid &grid);
    static void initChaos(Grid &grid, float density = 0.3f);

    // Dispatcher
    static void initPattern(Grid &grid, Pattern pattern);
    static const char *getPatternName(Pattern pattern);
};