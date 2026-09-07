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
    static constexpr size_t GRID_WIDTH = 30;
    static constexpr size_t GRID_HEIGHT = 30;
    static constexpr size_t GRID_DEPTH = 30;

    static constexpr int SURVIVE_MIN = 5;
    static constexpr int SURVIVE_MAX = 8;
    static constexpr int BORN_MIN = 5;
    static constexpr int BORN_MAX = 5;

    static constexpr float GENERATION_INTERVAL = 1.0f; // 1 generation/s
};