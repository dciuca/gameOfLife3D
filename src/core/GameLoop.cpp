#include "core/GameLoop.h"

#include "core/Config.h"
#include "core/GameRules.h"
#include "utils/Utils.h"
#include <memory>
#include <utility>

GameLoop::GameLoop(std::unique_ptr<IWindow> window,
                   std::unique_ptr<IRenderer> renderer,
                   std::unique_ptr<IInputHandler> inputHandler,
                   std::unique_ptr<ICamera> camera,
                   std::shared_ptr<GridPair> gridPair)
    : m_gridPair(std::move(gridPair)), m_camera(std::move(camera)),
      m_inputHandler(std::move(inputHandler)), m_renderer(std::move(renderer)),
      m_window(std::move(window)) {
  m_speedMultiplier = 1.0f;
  m_gridChanged = false;
  m_gameRules = std::make_unique<GameRules>();
  PatternLibrary::initPattern(m_gridPair->current(),
                              GameConfig::INITIAL_PATTERN);
}

void GameLoop::Run() {
  Utils::Timer computeTimer;
  Utils::Timer drawTimer;

  float simulationTime = 0.0f;

  while (!m_window->shouldClose()) {
    m_inputHandler->update();

    if (!m_inputHandler->isPaused()) {
      float dt = m_window->getTimeFrame();
      simulationTime += dt * m_speedMultiplier;

      // Time Slicing
      while (simulationTime >= GameConfig::GENERATION_INTERVAL) {
        computeTimer.reset();

        m_gameRules->computeNextGeneration(
            *m_gridPair, GameConfig::SURVIVE_MIN, GameConfig::SURVIVE_MAX,
            GameConfig::BORN_MIN, GameConfig::BORN_MAX);
        m_gridPair->swap();

        simulationTime -= GameConfig::GENERATION_INTERVAL;
        m_gridChanged = true;

        computeTimer.stop();
      }

      if (m_gridChanged) {
        m_renderer->collectCellTransforms();
        m_gridChanged = false;
      }
    }

    drawTimer.reset();
    m_renderer->beginFrame();
    m_renderer->renderGrid();
    m_renderer->drawStats(
        m_inputHandler->isPaused(), computeTimer.elapsedMilliseconds(),
        drawTimer.elapsedMilliseconds(), AppConfig::TARGET_FPS);
    m_renderer->endFrame();
    drawTimer.stop();
  }
}