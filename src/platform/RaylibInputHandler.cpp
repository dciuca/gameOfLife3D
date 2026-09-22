#include "platform/RaylibInputHandler.h"
#include "platform/RaylibCamera.h"

RaylibInputHandler::RaylibInputHandler(RaylibCamera &camera)
    : m_isPaused(false),
      m_mouseSensitivity(0.001f),
      m_camera(camera) {};

void RaylibInputHandler::update()
{
    // --------------------------------------
    // PAUSE HANDLING
    // --------------------------------------
    if (IsKeyPressed(KEY_P))
    {
        m_isPaused = !m_isPaused;
    }

    // --------------------------------------
    // CAMERA ROTATION
    // --------------------------------------
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 delta = GetMouseDelta();

        m_camera.yaw(-delta.x * m_mouseSensitivity);
        m_camera.pitch(-delta.y * m_mouseSensitivity);
    }

    // --------------------------------------
    // CAMERA ZOOM
    // --------------------------------------
    float wheel = GetMouseWheelMove();
    if (wheel != 0.0f)
    {
        m_camera.zoom(-wheel);
    }
}

// --------------------------------------
// PAUSE HANDLING
// --------------------------------------
bool RaylibInputHandler::isPaused()
{
    return m_isPaused;
}