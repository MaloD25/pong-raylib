#include "GamePlay.h"
#include <cmath>

Game::Game() {
	Field = LoadTexture("assets/Field.png");

    
}



void Game::Update(Paddle& player, Paddle& enemy, Ball& b, float dt) {

    if (state == GameState::MENU)
    {
        MenuAction action = menu.Update(dt);

        if (action == MenuAction::PLAY_SOLO)
        {
            mode = GameMode::SOLO;
            ResetMatch(player, enemy, b);
            state = GameState::PLAYING;
        }
        else if (action == MenuAction::PLAY_VERSUS)
        {
            mode = GameMode::VERSUS;
            ResetMatch(player, enemy, b);
            state = GameState::PLAYING;
        }
        else if (action == MenuAction::QUIT)
        {
            CloseWindow();
        }
    }

    else if (state == GameState::PLAYING)
    {
        player.Update(dt);

        if (mode == GameMode::SOLO)
        {
            enemy.UpdateAI(dt, b.pos.y);
        }
        else if (mode == GameMode::VERSUS)
        {
            enemy.UpdatePlayer2(dt);
        }

        b.Update();

        Rectangle ballRect = { b.pos.x - b.radius, b.pos.y - b.radius, b.radius * 2, b.radius * 2 };

        Rectangle playerRect = { player.pos.x, player.pos.y, player.l / 4, player.l };
        Rectangle enemyRect = { enemy.pos.x, enemy.pos.y, enemy.l / 4, enemy.l };

        if (CheckCollisionRecs(ballRect, playerRect))
        {
            float overlapLeft = (ballRect.x + ballRect.width) - playerRect.x;
            float overlapRight = (playerRect.x + playerRect.width) - ballRect.x;
            float overlapTop = (ballRect.y + ballRect.height) - playerRect.y;
            float overlapBottom = (playerRect.y + playerRect.height) - ballRect.y;

            float minOverlapX = (overlapLeft < overlapRight) ? overlapLeft : overlapRight;
            float minOverlapY = (overlapTop < overlapBottom) ? overlapTop : overlapBottom;

            if (minOverlapX < minOverlapY)
            {
                if (ballRect.x < playerRect.x)
                {
                    b.pos.x = playerRect.x - b.radius;
                }
                else
                {
                    b.pos.x = playerRect.x + playerRect.width + b.radius;
                }

                float paddleCenterY = player.pos.y + player.l / 2.0f;
                float hitPos = (b.pos.y - paddleCenterY) / (player.l / 2.0f);

                if (hitPos < -1.0f) hitPos = -1.0f;
                if (hitPos > 1.0f) hitPos = 1.0f;

                float speedX = std::fabs(b.velocity.x);
                float maxBounceY = 500.0f;

                b.velocity.x = speedX;
                b.velocity.y = hitPos * maxBounceY;
            }
            else
            {
                if (ballRect.y < playerRect.y)
                {
                    b.pos.y = playerRect.y - b.radius;
                }
                else
                {
                    b.pos.y = playerRect.y + playerRect.height + b.radius;
                }

                b.velocity.y *= -1;
            }
        }

        if (CheckCollisionRecs(ballRect, enemyRect))
        {
            float overlapLeft = (ballRect.x + ballRect.width) - enemyRect.x;
            float overlapRight = (enemyRect.x + enemyRect.width) - ballRect.x;
            float overlapTop = (ballRect.y + ballRect.height) - enemyRect.y;
            float overlapBottom = (enemyRect.y + enemyRect.height) - ballRect.y;

            float minOverlapX = (overlapLeft < overlapRight) ? overlapLeft : overlapRight;
            float minOverlapY = (overlapTop < overlapBottom) ? overlapTop : overlapBottom;

            if (minOverlapX < minOverlapY)
            {
                if (ballRect.x < enemyRect.x)
                {
                    b.pos.x = enemyRect.x - b.radius;
                }
                else
                {
                    b.pos.x = enemyRect.x + enemyRect.width + b.radius;
                }

                float paddleCenterY = enemy.pos.y + enemy.l / 2.0f;
                float hitPos = (b.pos.y - paddleCenterY) / (enemy.l / 2.0f);

                if (hitPos < -1.0f) hitPos = -1.0f;
                if (hitPos > 1.0f) hitPos = 1.0f;

                float speedX = std::fabs(b.velocity.x);
                float maxBounceY = 500.0f;

                b.velocity.x = -speedX;
                b.velocity.y = hitPos * maxBounceY;
            }
            else
            {
                if (ballRect.y < enemyRect.y)
                {
                    b.pos.y = enemyRect.y - b.radius;
                }
                else
                {
                    b.pos.y = enemyRect.y + enemyRect.height + b.radius;
                }

                b.velocity.y *= -1;
            }
        }

        if (b.pos.x + b.radius < 0)
        {
            rightScore++;

            if (rightScore >= maxScore)
            {
                winner = 2;
                state = GameState::GAMEOVER;
            }
            else
            {
                ResetBall(b, false);
                state = GameState::POINT_PAUSE;
            }
        }

        if (b.pos.x - b.radius > 800)
        {
            leftScore++;

            if (leftScore >= maxScore)
            {
                winner = 1;
                state = GameState::GAMEOVER;
            }
            else
            {
                ResetBall(b, true);
                state = GameState::POINT_PAUSE;
            }
        }
    }

    else if (state == GameState::POINT_PAUSE)
    {
        if (IsKeyPressed(KEY_R))
        {
            state = GameState::PLAYING;
        }
    }

    else if (state == GameState::GAMEOVER)
    {
        if (IsKeyPressed(KEY_R))
        {
            ResetMatch(player, enemy, b);
            state = GameState::PLAYING;
        }

        if (IsKeyPressed(KEY_C))
        {
            state = GameState::MENU;
        }
}
}

void Game::ResetMatch(Paddle& player, Paddle& enemy, Ball& b)
{
    leftScore = 0;
    rightScore = 0;

    player.pos = { 50, 160 };
    enemy.pos = { 720, 160 };

    ResetBall(b, true);
}

void Game::ResetBall(Ball& b, bool toRight)
{
    b.pos = { 400, 225 };

    if (toRight)
    {
        b.velocity = { 600.0f , 0.0f };
    }
    else
    {
        b.velocity = { -600.0f , 0.0f };
    }
}

void Game::Draw(Paddle& player, Paddle& enemy, Ball& b) {

    if (state == GameState::MENU)
    {
        menu.Draw();
        return;
    }

    Rectangle source = { 0, 0, (float)Field.width, (float)Field.height };
    Rectangle dest = { 0, 0, 800, 450 };

    DrawTexturePro(Field, source, dest, { 0,0 }, 0, WHITE);

    player.Draw();
    enemy.Draw();
    b.Draw();

    DrawText(TextFormat("%d", leftScore), 300, 20, 50, WHITE);
    DrawText(TextFormat("%d", rightScore), 470, 20, 50, WHITE);

    if (state == GameState::POINT_PAUSE)
    {
        DrawText("Appuie sur R pour reprendre", 200, 200, 30, WHITE);
    }

    if (state == GameState::GAMEOVER)
    {
        if (winner == 1)
        {
            DrawText("Le joueur de gauche gagne !", 180, 160, 35, WHITE);
        }
        else if (winner == 2)
        {
            DrawText("Le joueur de droite gagne !", 180, 160, 35, WHITE);
        }

        DrawText("Appuie sur R pour recommencer", 170, 230, 25, WHITE);
        DrawText("Appuie sur C pour retourner au menu", 140, 270, 25, WHITE);
    }
}

