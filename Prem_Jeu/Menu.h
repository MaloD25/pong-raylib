
#pragma once
#include "raylib.h"

enum class MenuAction {
    NONE,
    PLAY_SOLO,
    PLAY_VERSUS,
    QUIT
};

class Menu {
public:
    static const int frameCount = 9;

    Texture2D frames[frameCount];
    int currentFrame = 0;
    float animTimer = 0.0f;
    float animSpeed = 0.12f;

    Rectangle soloButton = { 275, 170, 250, 60 };
    Rectangle versusButton = { 275, 250, 250, 60 };
    Rectangle quitButton = { 275, 330, 250, 60 };

    Menu();

    MenuAction Update(float dt);
    void Draw();
};