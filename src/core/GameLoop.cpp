#include "GameLoop.h"
#include "Config.h"
#include "raylib.h"
#include "Utils.h"

GameLoop::GameLoop()
    : m_currentGrid(std::make_unique<Grid>(GameConfig::GRID_WIDTH, GameConfig::GRID_HEIGHT, GameConfig::GRID_DEPTH)),
      m_nextGrid(std::make_unique<Grid>(GameConfig::GRID_WIDTH, GameConfig::GRID_HEIGHT, GameConfig::GRID_DEPTH))
{
}

void GameLoop::Run()
{
    // DEBUG
    Utils::log("Starting...", Utils::LogLevel::INFO);
    Utils::Timer timer;
    // ----------------------

    while (!WindowShouldClose())
    {
        // DEBUG ----------------
        // timer.reset();
        // ----------------------

        BeginDrawing();
        ClearBackground(RAYWHITE);

        EndDrawing();

        // DEBUG ----------------
        // timer.stop();
        // Utils::log("Loop: " + std::to_string(timer.elapsedMilliseconds()) + " us", Utils::LogLevel::DEBUG);
        // ----------------------
    }
    CloseWindow();
}