#pragma once

class Grid;

class IRenderer {
public:
  virtual ~IRenderer() = default;

  virtual void beginFrame() = 0;
  virtual void endFrame() = 0;
  virtual void renderGrid() = 0;
  virtual void drawStats(bool paused, double computeMs, double drawMs,
                         int fps) = 0;
  virtual void onGridChanged(const Grid &grid) = 0;
};