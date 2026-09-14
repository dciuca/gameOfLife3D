#include "GameLoop.h"
#include "Config.h"
#include "Utils.h"

#include "RaylibInputHandler.h"
#include "RaylibRenderer.h"
#include "RaylibWindow.h"

GameLoop::GameLoop(
    std::unique_ptr<IWindow> window)
    // std::unique_ptr<ICamera> camera)
    : m_currentGrid(std::make_unique<Grid>(GameConfig::GRID_WIDTH, GameConfig::GRID_HEIGHT, GameConfig::GRID_DEPTH)),
      m_nextGrid(std::make_unique<Grid>(GameConfig::GRID_WIDTH, GameConfig::GRID_HEIGHT, GameConfig::GRID_DEPTH)),
      m_speedMultiplier(1.0f),
      m_gridChanged(false),
      m_window(std::move(window))
//   m_camera(std::move(camera))
{
    initPattern(GameConfig::INITIAL_PATTERN);
    m_camera = std::make_unique<RaylibCamera>();
    m_renderer = std::make_unique<RaylibRenderer>(*m_currentGrid);
    m_inputHandler = std::make_unique<RaylibInputHandler>();
}

void GameLoop::Run()
{
    Utils::Timer computeTimer;
    Utils::Timer drawTimer;

    float simulationTime = 0.0f;

    while (!m_window->shouldClose())
    {
        m_inputHandler->update(*m_camera);

        if (!m_inputHandler->isPaused())
        {
            float dt = GetFrameTime();
            simulationTime += dt * m_speedMultiplier;

            // Time Slicing
            while (simulationTime >= GameConfig::GENERATION_INTERVAL)
            {
                computeTimer.reset();

                computeNextGeneration();
                swapBuffers();
                simulationTime -= GameConfig::GENERATION_INTERVAL;
                m_gridChanged = true;

                computeTimer.stop();
            }

            if (m_gridChanged)
            {
                m_renderer->collectCellTransforms();
                m_gridChanged = false;
            }
        }

        drawTimer.reset();
        m_renderer->beginFrame();
        m_renderer->renderGrid(*m_camera);
        m_renderer->drawStats(
            m_inputHandler->isPaused(),
            computeTimer.elapsedMilliseconds(),
            drawTimer.elapsedMilliseconds(),
            RaylibConfig::TARGET_FPS);
        m_renderer->endFrame();
        drawTimer.stop();
    }
    m_window->shutdown();
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