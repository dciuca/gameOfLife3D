// include/rendering/Renderer.h
#pragma once

#include "core/ICamera.h"

class IRenderer
{
public:
    virtual ~IRenderer() = default;

    virtual void beginFrame() = 0;
    virtual void endFrame() = 0;
    virtual void renderGrid() = 0;
    virtual void drawStats(bool paused, double computeMs, double drawMs, int fps) = 0;
    virtual void collectCellTransforms() = 0;

private:
    virtual void initMesh() = 0;
    virtual void initInstancedShader() = 0;
    virtual void initBackground() = 0;
};