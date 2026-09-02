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

    /// It swaps the current and the next grid pointers
    void swapBuffers()
    {
        m_currentGrid.swap(m_nextGrid);
    }

private:
    std::unique_ptr<Grid> m_currentGrid;
    std::unique_ptr<Grid> m_nextGrid;
};