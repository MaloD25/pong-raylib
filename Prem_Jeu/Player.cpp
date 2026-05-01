#include "Player.h"

Player::Player(Vector2 startPos, float size)
    : pos(startPos), l(size)
{
}

void Player::Update()
{
    float dt = GetFrameTime();

    if (IsKeyDown(KEY_RIGHT)) pos.x += speed * dt;
    if (IsKeyDown(KEY_LEFT)) pos.x -= speed * dt;

    if (pos.x < 0) pos.x = 0;
    if (pos.x > 400 - l) pos.x = 400 - l;
}

void Player::Draw() const
{
    DrawRectangle(pos.x, pos.y, l, l, RED);
}


   