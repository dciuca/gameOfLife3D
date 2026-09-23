#pragma once

#include "core/IInputHandler.h"

class RaylibInputHandler : public IInputHandler
{
public:
    RaylibInputHandler();

    InputState poll() override;

private:
    float m_rotateSensitivity;
    float m_panSensitivity;
};