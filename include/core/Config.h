#pragma once

#include <cstddef>

struct RaylibConfig
{
    static constexpr int TARGET_FPS = 60;
    static constexpr int SCREEN_WIDTH = 800;
    static constexpr int SCREEN_HEIGHT = 600;
};

struct GameConfig
{
    static constexpr size_t GRID_WIDTH = 100;
    static constexpr size_t GRID_HEIGHT = 100;
    static constexpr size_t GRID_DEPTH = 100;

    static constexpr float GENERATION_INTERVAL = 1.0f; // 1 generation/s
};