#pragma once

#include "core/IRenderer.h"
#include "raylib.h"

#include <array>
#include <cstdint>
#include <vector>

class RaylibCamera; // forward declaration

class RaylibRenderer : public IRenderer {
public:
  RaylibRenderer(RaylibCamera &camera);
  ~RaylibRenderer();

  void beginFrame() override;
  void endFrame() override;
  void renderGrid() override;
  void drawStats(bool paused, double computeMs, double drawMs,
                 float speedMultiplier) override;
  void onGridChanged(const Grid &grid) override;

private:
  void initMesh();
  void initInstancedShader();
  void initBackground();

private:
  RaylibCamera &m_camera;
  float m_cellSize = 0.9f;
  Mesh m_cubeMesh;
  Material m_instancedMaterial;
  Shader m_instancingShader;
  static constexpr size_t AGE_BUCKETS = 4;
  std::array<std::vector<Matrix>, AGE_BUCKETS> m_transformsByAge;
  std::vector<uint8_t> m_cellAges; // same flat layout as Grid, 0 = dead
  size_t m_aliveCount = 0;
  int m_cubeColorLoc = -1;
  Texture2D m_backgroundTexture;
};