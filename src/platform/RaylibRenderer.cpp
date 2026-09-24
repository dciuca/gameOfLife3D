#include "platform/RaylibRenderer.h"
#include "core/Grid.h"
#include "platform/RaylibCamera.h"
#include "raylib.h"

#include "raymath.h"
#include <string>
#include <vector>

#define GLSL_VERSION 330

RaylibRenderer::RaylibRenderer(RaylibCamera &camera) : m_camera(camera) {
  initMesh();
  initBackground();
}

RaylibRenderer::~RaylibRenderer() {
  UnloadMesh(m_cubeMesh);
  UnloadMaterial(m_instancedMaterial);
  UnloadTexture(m_backgroundTexture);
}

void RaylibRenderer::beginFrame() {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawTexturePro(m_backgroundTexture,
                 {0, 0, (float)m_backgroundTexture.width,
                  (float)m_backgroundTexture.height},
                 {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
                 {0, 0}, 0.0f, WHITE);
}

void RaylibRenderer::endFrame() {
  DrawFPS(10, 10);
  EndDrawing();
}

void RaylibRenderer::renderGrid() {
  BeginMode3D(m_camera.getCamera());

  float cameraPos[3] = {m_camera.getCamera().position.x,
                        m_camera.getCamera().position.y,
                        m_camera.getCamera().position.z};
  SetShaderValue(m_instancingShader,
                 m_instancingShader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos,
                 SHADER_UNIFORM_VEC3);

  if (!m_transforms.empty()) {
    DrawMeshInstanced(m_cubeMesh, m_instancedMaterial, m_transforms.data(),
                      static_cast<int>(m_transforms.size()));
  }

  EndMode3D();
}

void RaylibRenderer::drawStats(bool paused, double computeMs, double drawMs,
                               int fps) {
  // HUD Line 1 (Compute Stat)
  std::string line1;
  if (paused) {
    line1 = "PAUSED (press P to resume)";
  } else {
    line1 = std::to_string(m_transforms.size()) +
            " CELLS | compute: " + std::to_string(computeMs) + " ms";
  }

  // HUD Line 2 (Draw Stat)
  std::string line2 = "TARGET FPS: " + std::to_string(fps) +
                      " | draw: " + std::to_string(drawMs) + " ms";

  double frameBudgetMs = 1000.0 / fps;
  Color line2Color = (drawMs <= frameBudgetMs) ? GREEN : RED;

  // Draw HUD
  int y = 40;
  DrawText(line1.c_str(), 10, y, 20, paused ? YELLOW : BLUE);
  DrawText(line2.c_str(), 10, y + 25, 20, line2Color);
}

void RaylibRenderer::onGridChanged(const Grid &grid) {
  const auto &data = grid.getGridDataReadOnly();

  const size_t W = grid.getWidth();
  const size_t H = grid.getHeight();
  const size_t D = grid.getDepth();

  const size_t logicW = W - 2 * Grid::GUARD_CELL;
  const size_t logicH = H - 2 * Grid::GUARD_CELL;
  const size_t logicD = D - 2 * Grid::GUARD_CELL;

  const float offsetX = static_cast<float>(logicW) / 2.0f;
  const float offsetY = static_cast<float>(logicH) / 2.0f;
  const float offsetZ = static_cast<float>(logicD) / 2.0f;

  // clear() keeps the capacity: memory grows only up to the peak of alive
  // cells and is reused by the next generations
  m_transforms.clear();

  std::vector<float> xCoords(logicW);
  std::vector<float> yCoords(logicH);
  std::vector<float> zCoords(logicD);

  for (size_t x = 1; x <= logicW; x++) {
    xCoords[x - 1] = static_cast<float>(x - 1) - offsetX;
  }
  for (size_t y = 1; y <= logicH; y++) {
    yCoords[y - 1] = static_cast<float>(y - 1) - offsetY;
  }
  for (size_t z = 1; z <= logicD; z++) {
    zCoords[z - 1] = static_cast<float>(z - 1) - offsetZ;
  }

  for (size_t z = 1; z <= logicD; z++) {
    float fz = zCoords[z - 1];
    for (size_t y = 1; y <= logicH; y++) {
      float fy = yCoords[y - 1];
      for (size_t x = 1; x <= logicW; x++) {
        size_t idx = x + y * W + z * W * H;

        if (data[idx] == 1) {
          float fx = xCoords[x - 1];

          Matrix transform = MatrixTranslate(fx, fy, fz);
          Matrix scale = MatrixScale(m_cellSize, m_cellSize, m_cellSize);
          Matrix final = MatrixMultiply(scale, transform);

          m_transforms.push_back(final);
        }
      }
    }
  }
}

// private
void RaylibRenderer::initMesh() {
  m_cubeMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
  initInstancedShader();
}

void RaylibRenderer::initInstancedShader() {
  m_instancingShader = LoadShader("resources/shaders/glsl330/instancing.vs",
                                  "resources/shaders/glsl330/instancing.fs");

  m_instancingShader.locs[SHADER_LOC_MATRIX_MVP] =
      GetShaderLocation(m_instancingShader, "mvp");

  m_instancedMaterial = LoadMaterialDefault();
  m_instancedMaterial.shader = m_instancingShader;
  m_instancedMaterial.maps[MATERIAL_MAP_DIFFUSE].color = BLUE;

  // Light Position
  int lightLoc = GetShaderLocation(m_instancingShader, "lightPos");
  float lightPos[3] = {m_camera.getCamera().position.x,
                       m_camera.getCamera().position.y + 20.0f,
                       m_camera.getCamera().position.z};
  SetShaderValue(m_instancingShader, lightLoc, lightPos, SHADER_UNIFORM_VEC3);
}

void RaylibRenderer::initBackground() {
  m_backgroundTexture = LoadTexture("resources/textures/bckg.png");
}