#include "core/GameRules.h"

GameRules::GameRules() {}

void GameRules::computeNextGeneration(std::shared_ptr<GridPair> gridPair,
                                      size_t sMin, size_t sMax, size_t bMin,
                                      size_t bMax) {
  const auto &currentData = gridPair->current().getGridData();
  auto &nextData = gridPair->next().getGridData();

  // Get Physical Dimensions (including guard cells)
  const size_t physWidth = gridPair->current().getWidth();
  const size_t physHeight = gridPair->current().getHeight();
  const size_t physDepth = gridPair->current().getDepth();
  const size_t physWH = physWidth * physHeight;

  // Get the Cell pre-computed offsets
  const auto &offsets = gridPair->current().getOffsets();

  // Get Logical Dimensions (no guard cells)
  const size_t logicWidth = physWidth - 2 * Grid::GUARD_CELL;
  const size_t logicHeight = physHeight - 2 * Grid::GUARD_CELL;
  const size_t logicDepth = physDepth - 2 * Grid::GUARD_CELL;

  gridPair->next().resetGrid();

  for (size_t z = 1; z <= logicDepth; z++) {
    for (size_t y = 1; y <= logicHeight; y++) {
      for (size_t x = 1; x <= logicWidth; x++) {
        // Physical Index (with guard cells)
        size_t idx = x + y * physWidth + z * physWH;

        // Neighbors Count
        int neighbors = 0;
        for (int offset : offsets) {
          neighbors += currentData[idx + offset];
        }

        // Apply the Game Of Life Rules
        bool isAlive = currentData[idx];
        if (isAlive) {
          nextData[idx] = (neighbors >= sMin && neighbors <= sMax) ? 1 : 0;
        } else {
          nextData[idx] = (neighbors >= bMin && neighbors <= bMax) ? 1 : 0;
        }
      }
    }
  }
}