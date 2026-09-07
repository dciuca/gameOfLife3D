#include "Renderer.h"

Renderer::Renderer()
{
    initCamera();
}

void Renderer::beginFrame()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
}

void Renderer::endFrame()
{
    DrawFPS(10, 10);
    EndDrawing();
}

void Renderer::renderGrid(const Grid &grid)
{
    BeginMode3D(m_camera);

    const auto &data = grid.getGridDataReadOnly();

    const size_t logicWidth = grid.getWidth() - Grid::GUARD_CELL;
    const size_t logicHeight = grid.getHeight() - Grid::GUARD_CELL;
    const size_t logicDepth = grid.getDepth() - Grid::GUARD_CELL;

    const size_t physWidth = grid.getWidth();
    const size_t physHeight = grid.getHeight();
    const size_t physWH = physWidth * physHeight;

    // Offset per centrare la griglia nell'origine (0,0,0)
    const float offsetX = static_cast<float>(logicWidth) / 2.0f;
    const float offsetY = static_cast<float>(logicHeight) / 2.0f;
    const float offsetZ = static_cast<float>(logicDepth) / 2.0f;

    // Itera sulle celle logiche (da 1 a W, da 1 a H, da 1 a D)
    for (size_t z = 1; z <= logicDepth; z++)
    {
        for (size_t y = 1; y <= logicHeight; y++)
        {
            for (size_t x = 1; x <= logicWidth; x++)
            {
                size_t idx = x + y * physWidth + z * physWH;

                if (data[idx] == 1)
                {
                    // Coordinate 3D centrate
                    float fx = static_cast<float>(x - 1) - offsetX;
                    float fy = static_cast<float>(y - 1) - offsetY;
                    float fz = static_cast<float>(z - 1) - offsetZ;

                    drawCell(fx, fy, fz, true);
                }
            }
        }
    }

    // TEST
    // DrawCube({0, 0, 0}, 1.0f, 1.0f, 1.0f, RED);
    // DrawCubeWires({0, 0, 0}, 1.0f, 1.0f, 1.0f, BLACK);

    EndMode3D();
}

void Renderer::drawCell(float x, float y, float z, bool alive)
{
    if (alive)
    {
        // Cella viva: cubo pieno con colore
        DrawCube({x, y, z}, m_cellSize, m_cellSize, m_cellSize, GREEN);
        // Bordo nero per definizione (opzionale)
        DrawCubeWires({x, y, z}, m_cellSize, m_cellSize, m_cellSize, DARKGREEN);
    }
}

void Renderer::updateCamera()
{
    UpdateCamera(&m_camera, CAMERA_ORBITAL);
}

// private
void Renderer::initCamera()
{
    m_camera.position = {0.0f, 10.0f, 10.0f}; // Camera position
    m_camera.target = {0.0f, 0.0f, 0.0f};     // Camera looking at point
    m_camera.up = {0.0f, 1.0f, 0.0f};         // Camera up vector (rotation towards target)
    m_camera.fovy = 45.0f;                    // Camera field-of-view Y
    m_camera.projection = CAMERA_PERSPECTIVE; // Camera mode type
}