#pragma once

#include "core/Grid.h"

#include <cstddef>
#include <memory>

class GameRules {
public:
  GameRules();
  ~GameRules() = default;

  void computeNextGeneration(std::shared_ptr<GridPair> gridPair, size_t sMin,
                             size_t sMax, size_t bMin, size_t bMax);
};