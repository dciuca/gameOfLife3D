#include "inputHandler.h"
#include "raylib.h"
#include "rcamera.h"

InputHandler::InputHandler()
    : m_isPaused(false), m_mouseSensitivity(0.001f)
{
}

void InputHandler::update(Camera3D &camera)
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

        CameraYaw(&camera, -delta.x * m_mouseSensitivity, true);
        CameraPitch(&camera, -delta.y * m_mouseSensitivity, true, true, true);
    }

    // --------------------------------------
    // CAMERA ZOOM
    // --------------------------------------
    float wheel = GetMouseWheelMove();
    if (wheel != 0.0f)
    {
        CameraMoveToTarget(&camera, -wheel);
    }
}

bool InputHandler::isPaused()
{
    return m_isPaused;
}