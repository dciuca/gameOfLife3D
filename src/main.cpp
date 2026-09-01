#include "GameLoop.h"
#include "raylib.h"

int main()
{
    InitWindow(800, 600, "Game Of Life");
    SetTargetFPS(60);

    GameLoop gameLoop;
    gameLoop.Run();

    CloseWindow();
}