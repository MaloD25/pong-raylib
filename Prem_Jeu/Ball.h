#pragma once
#include "raylib.h"

class Ball {
public:

    Vector2 pos;
    Vector2 velocity = { 600.0f , 500.0f };
    float radius;

    Ball(Vector2 startPos, float r);

    void Update();
    void Draw() const;

    
};