#pragma once

#include "core/ICamera.h"

class IInputHandler
{
public:
    virtual ~IInputHandler() = default;

    virtual void update() = 0;
    virtual bool isPaused() = 0;
};