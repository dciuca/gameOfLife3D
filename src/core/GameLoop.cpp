#include "GameLoop.h"
#include "Config.h"
#include "raylib.h"
#include "Utils.h"

GameLoop::GameLoop()
    : m_currentGrid(std::make_unique<Grid>(GameConfig::GRID_WIDTH, GameConfig::GRID_HEIGHT, GameConfig::GRID_DEPTH)),
      m_nextGrid(std::make_unique<Grid>(GameConfig::GRID_WIDTH, GameConfig::GRID_HEIGHT, GameConfig::GRID_DEPTH)),
      m_speedMultiplier(1.0f)
{
}

void GameLoop::Run()
{
    // DEBUG
    Utils::log("Starting...", Utils::LogLevel::INFO);
    Utils::Timer timer;
    // ----------------------

    float simulationTime = 0.0f;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        simulationTime += dt * m_speedMultiplier;

        // Time Slicing
        while (simulationTime >= GameConfig::GENERATION_INTERVAL)
        {
            // DEBUG ----------------
            timer.reset();
            // ----------------------

            computeNextGeneration();
            swapBuffers();
            simulationTime -= GameConfig::GENERATION_INTERVAL;

            // DEBUG ----------------
            timer.stop();
            Utils::log("computeNextGeneration took: " + std::to_string(timer.elapsedMilliseconds()) + " us", Utils::LogLevel::DEBUG);
            // ----------------------
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        EndDrawing();
    }
    CloseWindow();
}

void GameLoop::computeNextGeneration()
{
    Utils::log("Computing next generation...", Utils::LogLevel::DEBUG);

    const auto &currentData = m_currentGrid->getGridData();
    auto &nextData = m_nextGrid->getGridData();

    // Get Physical Dimensions (including guard cells)
    const size_t physWidth = m_currentGrid->getWidth();
    const size_t physHeight = m_currentGrid->getHeight();
    const size_t physDepth = m_currentGrid->getDepth();
    const size_t physWH = physWidth * physHeight;

    // Get the Cell pre-computed offsets
    const auto &offsets = m_currentGrid->getOffsets();

    // Get Logical Dimensions (no guard cells)
    const size_t logicWidth = physWidth - 2 * Grid::GUARD_CELL;
    const size_t logicHeight = physHeight - 2 * Grid::GUARD_CELL;
    const size_t logicDepth = physDepth - 2 * Grid::GUARD_CELL;

    m_nextGrid->resetGrid();

    for (size_t z = 1; z <= logicDepth; z++)
    {
        for (size_t y = 1; y <= logicHeight; y++)
        {
            for (size_t x = 1; x <= logicWidth; x++)
            {
                // Physical Index (with guard cells)
                size_t idx = x + y * physWidth + z * physWH;

                // Neighbors Count
                int neighbors = 0;
                for (int offset : offsets)
                {
                    neighbors += currentData[idx + offset];
                }

                // Apply the Game Of Life Rules
                bool isAlive = currentData[idx];
                if (isAlive)
                {
                    nextData[idx] = (neighbors >= 5 && neighbors <= 7) ? 1 : 0;
                }
                else
                {
                    nextData[idx] = (neighbors == 6) ? 1 : 0;
                }
            }
        }
    }
}