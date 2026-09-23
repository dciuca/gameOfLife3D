#pragma once

#include "core/GameRules.h"
#include "core/Grid.h"
#include "core/ICamera.h"
#include "core/IInputHandler.h"
#include "core/IRenderer.h"
#include "core/IWindow.h"

#include <memory>

class GameLoop {
public:
  GameLoop(std::unique_ptr<IWindow> window, std::unique_ptr<IRenderer> renderer,
           std::unique_ptr<IInputHandler> inputHandler,
           std::unique_ptr<ICamera> camera, std::shared_ptr<GridPair> gridPair);

  ~GameLoop() = default;

  void Run();

private:
  void handleInput(const InputState &input);

private:
  std::unique_ptr<IWindow> m_window;
  std::shared_ptr<GridPair> m_gridPair;
  std::unique_ptr<ICamera> m_camera;
  std::unique_ptr<IInputHandler> m_inputHandler;
  std::unique_ptr<IRenderer> m_renderer;
  std::unique_ptr<GameRules> m_gameRules;
  float m_speedMultiplier;
  bool m_gridChanged;
  bool m_isPaused;
};