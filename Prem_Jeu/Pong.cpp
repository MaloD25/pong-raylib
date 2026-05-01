#include "raylib.h"
#include "Gameplay.h"



int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Pong de Malo Dufournier");
    SetTargetFPS(60);

    Game g;
    Paddle player({ 50, 160 }, 120);
    Paddle enemy({ 720, 160 }, 120);
    Ball b({ 400, 225 }, 10);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        g.Update(player, enemy, b, dt);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        g.Draw(player, enemy, b);
        DrawText("De Malo Dufournier", 600, 420, 20, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}