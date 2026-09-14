#pragma once

#include "raylib.h"
#include "../core/interfaces/IWindow.h"
#include "../core/Config.h"

class RaylibWindow : public IWindow
{
public:
    void init() override
    {
        InitWindow(RaylibConfig::SCREEN_WIDTH, RaylibConfig::SCREEN_HEIGHT, "Game Of Life");
        SetTargetFPS(RaylibConfig::TARGET_FPS);
    }
    void shutdown() override { CloseWindow(); }
    bool shouldClose() const override { return WindowShouldClose(); }
};