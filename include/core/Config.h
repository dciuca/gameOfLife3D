#pragma once

#include <cstddef>
#include "PatternLibrary.h"

struct RaylibConfig
{
    static constexpr int TARGET_FPS = 60;
    static constexpr int SCREEN_WIDTH = 1280;
    static constexpr int SCREEN_HEIGHT = 720;
};

struct GameConfig
{
    static constexpr size_t GRID_WIDTH = 50;
    static constexpr size_t GRID_HEIGHT = 50;
    static constexpr size_t GRID_DEPTH = 50;

    static constexpr PatternLibrary::Pattern INITIAL_PATTERN = PatternLibrary::Pattern::CHAOS_DENSE;

    // Rule B6/S567
    static constexpr int SURVIVE_MIN = 5;
    static constexpr int SURVIVE_MAX = 7;
    static constexpr int BORN_MIN = 6;
    static constexpr int BORN_MAX = 6;

    // Rule B5/S45
    // static constexpr int SURVIVE_MIN = 4;
    // static constexpr int SURVIVE_MAX = 5;
    // static constexpr int BORN_MIN = 5;
    // static constexpr int BORN_MAX = 5;

    static constexpr float GENERATION_INTERVAL = 2.0f; // 1 generation every 2s
};