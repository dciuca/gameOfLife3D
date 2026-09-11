#include "GameLoop.h"
#include "Config.h"
#include "raylib.h"
#include "Utils.h"

GameLoop::GameLoop()
    : m_currentGrid(std::make_unique<Grid>(GameConfig::GRID_WIDTH, GameConfig::GRID_HEIGHT, GameConfig::GRID_DEPTH)),
      m_nextGrid(std::make_unique<Grid>(GameConfig::GRID_WIDTH, GameConfig::GRID_HEIGHT, GameConfig::GRID_DEPTH)),
      m_speedMultiplier(1.0f),
      m_gridChanged(false)
{
    initPattern(GameConfig::INITIAL_PATTERN);
    m_renderer = std::make_unique<Renderer>(*m_currentGrid);
    m_inputHandler = InputHandler();
}

void GameLoop::Run()
{
    Utils::Timer timer;

    float simulationTime = 0.0f;

    while (!WindowShouldClose())
    {
        m_inputHandler.update(m_renderer->getCamera());

        if (!m_inputHandler.isPaused())
        {
            float dt = GetFrameTime();
            simulationTime += dt * m_speedMultiplier;

            // Time Slicing
            while (simulationTime >= GameConfig::GENERATION_INTERVAL)
            {
                timer.reset();

                computeNextGeneration();
                swapBuffers();
                simulationTime -= GameConfig::GENERATION_INTERVAL;
                m_gridChanged = true;

                timer.stop();
            }
        }
        std::string msg = (m_inputHandler.isPaused())
                              ? "GENERATION PAUSED (press P to reesume)"
                              : (std::to_string(GameConfig::GRID_WIDTH) + "x" + std::to_string(GameConfig::GRID_HEIGHT) + "x" + std::to_string(GameConfig::GRID_DEPTH) + " compute time: " + std::to_string(timer.elapsedMilliseconds()) + " ms");

        if (m_gridChanged)
        {
            m_renderer->collectCellTransforms();
            m_gridChanged = false;
        }

        // Render
        m_renderer->beginFrame();
        m_renderer->renderGrid();
        m_renderer->writeText(msg.data(), 20, {10, 40}, BLUE);
        m_renderer->endFrame();
    }
    CloseWindow();
}

void GameLoop::computeNextGeneration()
{
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
                    nextData[idx] = (neighbors >= GameConfig::SURVIVE_MIN &&
                                     neighbors <= GameConfig::SURVIVE_MAX)
                                        ? 1
                                        : 0;
                }
                else
                {
                    nextData[idx] = (neighbors >= GameConfig::BORN_MIN &&
                                     neighbors <= GameConfig::BORN_MAX)
                                        ? 1
                                        : 0;
                }
            }
        }
    }
}

void GameLoop::initPattern(PatternLibrary::Pattern pattern)
{
    m_initPattern = pattern;
    PatternLibrary::initPattern(*m_currentGrid, pattern);
    Utils::log("Pattern initialized: " +
                   std::string(PatternLibrary::getPatternName(pattern)),
               Utils::LogLevel::INFO);
}