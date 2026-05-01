#include "Enemy.h"


Enemy::Enemy(Vector2 startPos, float s)
    : pos(startPos), size(s)
{   
}

void Enemy::Update()
{
    float dt = GetFrameTime();
    pos.y += speed * dt;
}

void Enemy::Draw() const
{
    DrawRectangle(pos.x, pos.y, size, size, GRAY);
}