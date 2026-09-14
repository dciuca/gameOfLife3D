#pragma once

class IWindow
{
public:
    virtual ~IWindow() = default;
    virtual void init() = 0;
    virtual void shutdown() = 0;
    virtual bool shouldClose() const = 0;
};