#pragma once

#include <memory>
#include "Config.h"
#include "Grid.h"
#include "PatternLibrary.h"
#include "interfaces/IRenderer.h"
#include "interfaces/IInputHandler.h"
#include "interfaces/ICamera.h"
#include "interfaces/IWindow.h"

class GameLoop
{
public:
    GameLoop(
        std::unique_ptr<IWindow> window);
    // std::unique_ptr<ICamera> camera);
    ~GameLoop() = default;

    void Run();

private:
    void swapBuffers() { m_currentGrid.swap(m_nextGrid); }
    void computeNextGeneration();
    void initPattern(PatternLibrary::Pattern pattern);

private:
    std::unique_ptr<Grid> m_currentGrid;
    std::unique_ptr<Grid> m_nextGrid;
    std::unique_ptr<IRenderer> m_renderer;
    std::unique_ptr<IInputHandler> m_inputHandler;
    std::unique_ptr<ICamera> m_camera;
    std::unique_ptr<IWindow> m_window;

    PatternLibrary::Pattern m_initPattern;
    float m_speedMultiplier;
    bool m_gridChanged;
};