

#pragma once
#include "raylib.h"
#include "Paddle.h"
#include "Ball.h"
#include "Menu.h"

enum class GameState {
    MENU,
    PLAYING,
    POINT_PAUSE,
    GAMEOVER
};

enum class GameMode {
    SOLO,
    VERSUS
};

class Game {
public:
    Texture2D Field;

    int leftScore = 0;
    int rightScore = 0;
    int maxScore = 10;
    int winner = 0;

    GameState state = GameState::MENU;
    GameMode mode = GameMode::SOLO;

    Menu menu;

    Game();

    void Update(Paddle& player, Paddle& enemy, Ball& b, float dt);
    void Draw(Paddle& player, Paddle& enemy, Ball& b);

    void ResetBall(Ball& b, bool toRight);
    void ResetMatch(Paddle& player, Paddle& enemy, Ball& b);
};