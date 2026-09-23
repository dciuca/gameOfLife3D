#pragma once

#include "core/Config.h"
#include "core/IWindow.h"
#include "raylib.h"

class RaylibWindow : public IWindow {
public:
  ~RaylibWindow() { CloseWindow(); }

  void init() override {
    InitWindow(AppConfig::SCREEN_WIDTH, AppConfig::SCREEN_HEIGHT,
               "Game Of Life");
    SetTargetFPS(AppConfig::TARGET_FPS);
  }
  bool shouldClose() const override { return WindowShouldClose(); }
  float getTimeFrame() override { return GetFrameTime(); }
};