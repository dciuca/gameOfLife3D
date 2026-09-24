#pragma once

#include "core/IRenderer.h"
#include "raylib.h"

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
                 int fps) override;
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
  std::vector<Matrix> m_transforms; // one per alive cell
  Texture2D m_backgroundTexture;
};