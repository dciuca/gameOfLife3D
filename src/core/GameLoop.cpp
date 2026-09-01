#include "GameLoop.h"
#include "raylib.h"

GameLoop::GameLoop()
{
}

void GameLoop::Run()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Placeholder", GetScreenWidth() / 2, GetScreenHeight() / 2, 12, BLACK);
        EndDrawing();
    }
    CloseWindow();
}