#pragma once

#include "raylib.h"
#include "core/IRenderer.h"

class Grid;         // forward declaration
class RaylibCamera; // forward declaration

class RaylibRenderer : public IRenderer
{
public:
    RaylibRenderer(Grid &grid, RaylibCamera &camera);
    ~RaylibRenderer();

    void beginFrame() override;
    void endFrame() override;
    void renderGrid() override;
    void drawStats(bool paused, double computeMs, double drawMs, int fps) override;
    void collectCellTransforms() override;

private:
    void initMesh() override;
    void initInstancedShader() override;
    void initBackground() override;

private:
    Grid &m_grid;
    RaylibCamera &m_camera;
    float m_cellSize = 0.9f;
    Mesh m_cubeMesh;
    Material m_instancedMaterial;
    Shader m_instancingShader;
    int m_instanceCount = 0;
    Matrix *m_transforms;
    Texture2D m_backgroundTexture;
};