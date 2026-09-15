#include "core/Config.h"
#include <memory>

// Raylib Dependencies
#include "platform/RaylibWindow.h"
#include "platform/RaylibCamera.h"
#include "platform/RaylibInputHandler.h"
#include "platform/RaylibRenderer.h"

int main()
{
    // Composition Root for Raylib
    auto window = std::make_unique<RaylibWindow>();
    window->init();
    auto gridPair = std::make_shared<GridPair>(GameConfig::GRID_WIDTH, GameConfig::GRID_HEIGHT, GameConfig::GRID_DEPTH);
    auto camera = std::make_unique<RaylibCamera>();
    auto renderer = std::make_unique<RaylibRenderer>(*gridPair, *camera);
    auto inputHandler = std::make_unique<RaylibInputHandler>(*camera);

    //     GameLoop gameLoop(
    //         std::move(window),
    //         std::move(renderer),
    //         std::move(inputHandler),
    //         std::move(camera));
    //     gameLoop.Run();

    // window->shutdown();
    return 0;
}