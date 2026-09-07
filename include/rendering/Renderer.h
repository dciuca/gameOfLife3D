// include/rendering/Renderer.h
#pragma once

#include "raylib.h"
#include "Grid.h"

class Renderer
{
public:
    Renderer();
    ~Renderer() = default;

    // void setup(int screenWidth, int screenHeight);
    void beginFrame();
    void endFrame();

    void renderGrid(const Grid &grid);

    void updateCamera();
    // void resetCamera();

    Camera3D &getCamera() { return m_camera; }

private:
    Camera3D m_camera;
    bool m_isDragging = false;
    float m_cellSize = 0.9f;

    void initCamera();
    void drawCell(float x, float y, float z, bool alive);
};