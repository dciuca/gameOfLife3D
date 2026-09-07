#pragma once

#include <cstddef>

struct RaylibConfig
{
    static constexpr int TARGET_FPS = 60;
    static constexpr int SCREEN_WIDTH = 1280;
    static constexpr int SCREEN_HEIGHT = 720;
};

struct GameConfig
{
    static constexpr size_t GRID_WIDTH = 20;
    static constexpr size_t GRID_HEIGHT = 20;
    static constexpr size_t GRID_DEPTH = 20;

    static constexpr float GENERATION_INTERVAL = 1.0f; // 1 generation/s
};