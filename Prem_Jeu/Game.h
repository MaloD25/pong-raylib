
#pragma once
#include "raylib.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Game
{
public:

    Player player{ {400,400},30 };

    std::vector<Enemy> e;

    float spawnTimer = 0.0f;
    bool gameOver = false;

    void Update();
    void Draw();
};