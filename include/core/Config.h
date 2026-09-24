#pragma once

#include "PatternLibrary.h"
#include <cstddef>

struct AppConfig {
  static constexpr int TARGET_FPS = 60;
  static constexpr int SCREEN_WIDTH = 1280;
  static constexpr int SCREEN_HEIGHT = 720;
};

struct GameConfig {
  static constexpr size_t GRID_WIDTH = 500;
  static constexpr size_t GRID_HEIGHT = 4; // 3 = 2D game version
  static constexpr size_t GRID_DEPTH = 500;

  static constexpr PatternLibrary::Pattern INITIAL_PATTERN =
      PatternLibrary::Pattern::CHAOS_DENSE;

  // Rule B6/S567 (3D, set GRID_HEIGHT>=4)
  static constexpr int SURVIVE_MIN = 5;
  static constexpr int SURVIVE_MAX = 7;
  static constexpr int BORN_MIN = 6;
  static constexpr int BORN_MAX = 6;

  // Rule B3/S23 (2D, set GRID_HEIGHT=3)
  // static constexpr int SURVIVE_MIN = 2;
  // static constexpr int SURVIVE_MAX = 3;
  // static constexpr int BORN_MIN = 3;
  // static constexpr int BORN_MAX = 3;

  static constexpr float GENERATION_INTERVAL =
      0.25f; // 2.0f = 1 generation every 2s
};