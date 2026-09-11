#pragma once

#include <memory>
#include "Config.h"
#include "Grid.h"
#include "Renderer.h"
#include "PatternLibrary.h"
#include "inputHandler.h"

class GameLoop
{
public:
    GameLoop();
    ~GameLoop() = default;

    void Run();
    void setSpeedMultiplier(float multiplier) { m_speedMultiplier = multiplier; }

private:
    void swapBuffers() { m_currentGrid.swap(m_nextGrid); }
    void computeNextGeneration();
    void initPattern(PatternLibrary::Pattern pattern);

private:
    std::unique_ptr<Grid> m_currentGrid;
    std::unique_ptr<Grid> m_nextGrid;
    std::unique_ptr<Renderer> m_renderer;
    PatternLibrary::Pattern m_initPattern;
    InputHandler m_inputHandler;
    float m_speedMultiplier;
    bool m_gridChanged;
};