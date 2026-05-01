#include "Ball.h"

Ball::Ball(Vector2 startPos, float r)
    : pos(startPos), radius(r) {}

void Ball::Update()
{
    float dt = GetFrameTime();

    pos.x += velocity.x * dt;
    pos.y += velocity.y * dt;

    
    if (pos.y - radius <= 0)
    {
        pos.y = radius;
        velocity.y *= -1;
    }

    if (pos.y + radius >= 450)
    {
        pos.y = 450 - radius;
        velocity.y *= -1;
    }

   
}

void Ball::Draw() const
{
    DrawCircle(pos.x, pos.y, radius, RED);
}

