#pragma once

#include "raylib.h"

class InputHandler
{
public:
    InputHandler();
    ~InputHandler() = default;

    void update(Camera3D &camera);
    bool isPaused();

private:
    bool m_isPaused;
    float m_mouseSensitivity;
};