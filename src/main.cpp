#include "GameLoop.h"
#include "Config.h"

// Raylib framework
#include "RaylibWindow.h"
#include "RaylibCamera.h"

int main()
{
    auto window = std::make_unique<RaylibWindow>();
    window->init();
    auto camera = std::make_unique<RaylibCamera>();

    GameLoop gameLoop(
        std::move(window));
    // std::move(camera));
    gameLoop.Run();
}

// #include "GameLoop.h"
// #include "RaylibWindow.h"
// #include "RaylibRenderer.h"
// #include "RaylibInputHandler.h"
// #include "RaylibCamera.h"
// #include "Grid.h"

// int main()
// {
//     auto grid = std::make_shared<Grid>(/*...*/);
//     auto window = std::make_unique<RaylibWindow>();
//     auto camera = std::make_unique<RaylibCamera>();
//     auto renderer = std::make_unique<RaylibRenderer>(*grid);
//     auto input = std::make_unique<RaylibInputHandler>();

//     GameLoop gameLoop(
//         std::move(window),
//         std::move(renderer),
//         std::move(input),
//         std::move(camera));
//     gameLoop.Run();

//     return 0;
// }