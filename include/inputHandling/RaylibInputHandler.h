#pragma once

#include "../core/interfaces/IInputHandler.h"
#include "RaylibCamera.h"

class RaylibInputHandler : public IInputHandler
{
public:
    RaylibInputHandler()
        : m_isPaused(false), m_mouseSensitivity(0.001f) {};

    void update(ICamera &camera) override
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
    bool isPaused() override
    {
        return m_isPaused;
    }

private:
    bool m_isPaused;
    float m_mouseSensitivity;
};