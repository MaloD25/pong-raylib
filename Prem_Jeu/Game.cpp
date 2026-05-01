#include "Game.h"

void Game::Update()
{
    float dt = GetFrameTime();

    if (!gameOver)
    {
        player.Update();

        spawnTimer += dt;

        if (spawnTimer >= 0.5f)
        {
            spawnTimer = 0;

            float x = GetRandomValue(0, 360);
            float t = GetRandomValue(30, 70);
            e.push_back(Enemy({ x, -40}, t));
        }

        for (Enemy& enemy : e)
        {
            enemy.Update();

            Rectangle playerRect = { player.pos.x, player.pos.y, player.l, player.l };
            Rectangle enemyRect = { enemy.pos.x, enemy.pos.y, enemy.size, enemy.size };

            if (CheckCollisionRecs(playerRect, enemyRect))
            {
                gameOver = true;
            }
        }
    }
}

void Game::Draw()
{
    player.Draw();

    for (Enemy& enemy : e)
    {
        enemy.Draw();
    }

    if (gameOver)
    {
        DrawText("GAME OVER", 80, 200, 40, RED);
    }
}