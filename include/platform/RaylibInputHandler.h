#pragma once

#include "core/IInputHandler.h"
#include "platform/RaylibCamera.h"

class RaylibInputHandler : public IInputHandler
{
public:
    RaylibInputHandler();

    void update(ICamera &camera) override;
    bool isPaused() override;

private:
    bool m_isPaused;
    float m_mouseSensitivity;
};