// include/rendering/Renderer.h
#pragma once

#include "raylib.h"
#include "../core/interfaces/IRenderer.h"
#include "RaylibCamera.h"
#include "Grid.h"

class RaylibRenderer : public IRenderer
{
public:
    RaylibRenderer(const Grid &grid);
    ~RaylibRenderer();

    void beginFrame() override;
    void endFrame() override;
    void renderGrid(ICamera &camera) override;
    void drawStats(bool paused, double computeMs, double drawMs, int fps) override;
    void collectCellTransforms() override;

private:
    void initMesh() override;
    void initInstancedShader() override;
    void initBackground() override;

private:
    const Grid &m_grid;
    float m_cellSize = 0.9f;
    Mesh m_cubeMesh;
    Material m_instancedMaterial;
    Shader m_instancingShader;
    int m_instanceCount = 0;
    Matrix *m_transforms;
    Texture2D m_backgroundTexture;
};