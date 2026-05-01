#pragma once
#include "raylib.h"



class Player
{
public:

    Vector2 pos;
    float l;
    float speed = 400.0f;

    Player(Vector2 startPos, float size);

    void Update();
    void Draw() const;

    
};