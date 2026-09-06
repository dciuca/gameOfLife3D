#pragma once

#include <memory>
#include "Grid.h"
#include "Config.h"

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

private:
    std::unique_ptr<Grid> m_currentGrid;
    std::unique_ptr<Grid> m_nextGrid;
    float m_speedMultiplier;
};