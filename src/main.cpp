#include "GameLoop.h"
#include "raylib.h"
#include "Config.h"

int main()
{
    InitWindow(RaylibConfig::SCREEN_WIDTH, RaylibConfig::SCREEN_HEIGHT, "Game Of Life");
    SetTargetFPS(RaylibConfig::TARGET_FPS);

    GameLoop gameLoop;
    gameLoop.Run();

    CloseWindow();
}