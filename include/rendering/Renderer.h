// include/rendering/Renderer.h
#pragma once

#include "raylib.h"
#include "Grid.h"

class Renderer
{
public:
    Renderer(const Grid &grid);
    ~Renderer();

    void beginFrame();
    void endFrame();
    void renderGrid();
    Camera3D &getCamera() { return m_camera; };
    void drawStats(bool paused, double computeMs, double drawMs, int fps);
    void collectCellTransforms();

private:
    void initCamera();
    void initMesh();
    void initInstancedShader();
    void initBackground();

private:
    Camera3D m_camera;
    const Grid &m_grid;
    float m_cellSize = 0.9f;
    Mesh m_cubeMesh;
    Material m_instancedMaterial;
    Shader m_instancingShader;
    int m_instanceCount = 0;
    Matrix *m_transforms;
    Texture2D m_backgroundTexture;
};