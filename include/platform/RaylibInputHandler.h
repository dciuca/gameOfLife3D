#pragma once

#include "core/IInputHandler.h"

class RaylibCamera; // forward declaration

class RaylibInputHandler : public IInputHandler
{
public:
    RaylibInputHandler(RaylibCamera &camera);

    void update() override;
    bool isPaused() override;

private:
    bool m_isPaused;
    float m_mouseSensitivity;
    RaylibCamera &m_camera;
};