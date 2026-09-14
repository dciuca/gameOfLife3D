#pragma once

#include "ICamera.h"

class IInputHandler
{
public:
    virtual ~IInputHandler() = default;

    virtual void update(ICamera &camera) = 0;
    virtual bool isPaused() = 0;
};