#include "GameLoop.h"
#include "Config.h"
#include "raylib.h"
#include "Utils.h"

#include <random> // DEBUG

GameLoop::GameLoop()
    : m_currentGrid(std::make_unique<Grid>(GameConfig::GRID_WIDTH, GameConfig::GRID_HEIGHT, GameConfig::GRID_DEPTH)),
      m_nextGrid(std::make_unique<Grid>(GameConfig::GRID_WIDTH, GameConfig::GRID_HEIGHT, GameConfig::GRID_DEPTH)),
      m_speedMultiplier(1.0f)
{
    m_renderer = std::make_unique<Renderer>();
}

void GameLoop::Run()
{
    // DEBUG
    Utils::log("Starting...", Utils::LogLevel::INFO);
    Utils::Timer timer;

    // Pattern avvio
    // const int cx = GameConfig::GRID_WIDTH / 2;
    // const int cy = GameConfig::GRID_HEIGHT / 2;
    // const int cz = GameConfig::GRID_DEPTH / 2;

    // // Cubo 2x2x2 = 8 celle
    // for (int dz = 0; dz <= 1; dz++)
    // {
    //     for (int dy = 0; dy <= 1; dy++)
    //     {
    //         for (int dx = 0; dx <= 1; dx++)
    //         {
    //             m_currentGrid->setCellByPosition(cx + dx, cy + dy, cz + dz, 1);
    //         }
    //     }
    // }

    // Caos
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    const size_t w = m_currentGrid->getWidth();
    const size_t h = m_currentGrid->getHeight();
    const size_t d = m_currentGrid->getDepth();

    for (size_t z = 1; z < d - 1; z++)
    {
        for (size_t y = 1; y < h - 1; y++)
        {
            for (size_t x = 1; x < w - 1; x++)
            {
                if (dist(gen) < 0.3f)
                {
                    m_currentGrid->setCellByPosition(x, y, z, 1);
                }
            }
        }
    }
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
            Utils::log("computeNextGeneration took: " + std::to_string(timer.elapsedMilliseconds()) + " ms", Utils::LogLevel::DEBUG);

            // DEBUG: Verifica che le celle siano state impostate
            Utils::log("Verifica celle impostate:", Utils::LogLevel::INFO);
            for (size_t z = 0; z < 3; z++)
            {
                for (size_t y = 0; y < 3; y++)
                {
                    for (size_t x = 0; x < 3; x++)
                    {
                        uint8_t val = m_currentGrid->getCellByPosition(x, y, z);
                        if (val == 1)
                        {
                            Utils::log("Cella viva in (" + std::to_string(x) + "," +
                                           std::to_string(y) + "," + std::to_string(z) + ")",
                                       Utils::LogLevel::INFO);
                        }
                    }
                }
            }
            // ----------------------
        }

        // Render
        m_renderer->updateCamera();
        m_renderer->beginFrame();
        m_renderer->renderGrid(*m_currentGrid);
        m_renderer->endFrame();
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