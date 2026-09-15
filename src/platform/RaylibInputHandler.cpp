#pragma once

#include "platform/RaylibInputHandler.h"

RaylibInputHandler::RaylibInputHandler()
    : m_isPaused(false), m_mouseSensitivity(0.001f) {};

void RaylibInputHandler::update(ICamera &camera)
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

        camera.yaw(-delta.x * m_mouseSensitivity);
        camera.pitch(-delta.y * m_mouseSensitivity);
    }

    // --------------------------------------
    // CAMERA ZOOM
    // --------------------------------------
    float wheel = GetMouseWheelMove();
    if (wheel != 0.0f)
    {
        camera.zoom(-wheel);
    }
}

// --------------------------------------
// PAUSE HANDLING
// --------------------------------------
bool RaylibInputHandler::isPaused()
{
    return m_isPaused;
}