#pragma once

#include "core/Config.h"
#include "core/IWindow.h"
#include "raylib.h"

class RaylibWindow : public IWindow {
public:
  void init() override {
    InitWindow(AppConfig::SCREEN_WIDTH, AppConfig::SCREEN_HEIGHT,
               "Game Of Life");
    SetTargetFPS(AppConfig::TARGET_FPS);
  }
  void shutdown() override { CloseWindow(); }
  bool shouldClose() const override { return WindowShouldClose(); }
  float getTimeFrame() override { return GetFrameTime(); }
};