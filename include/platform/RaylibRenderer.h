#pragma once

#include "core/IRenderer.h"
#include "raylib.h"

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
  int m_instanceCount = 0;
  Matrix *m_transforms;
  Texture2D m_backgroundTexture;
};