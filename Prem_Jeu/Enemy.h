#pragma once
#include "raylib.h"


class Enemy
{
public:

    Vector2 pos;
    float size;
    float speed = 600.0f;

    Enemy(Vector2 startPos, float s);

    void Update();
    void Draw() const;
};