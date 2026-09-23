#pragma once

#include "core/Grid.h"

#include <cstddef>

class GameRules {
public:
  GameRules();
  ~GameRules() = default;

  void computeNextGeneration(GridPair &gridPair, size_t sMin, size_t sMax,
                             size_t bMin, size_t bMax);
};