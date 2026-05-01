#include "Menu.h"

Menu::Menu()
{
    frames[0] = LoadTexture("assets/menu/frame1.png");
    frames[1] = LoadTexture("assets/menu/frame2.png");
    frames[2] = LoadTexture("assets/menu/frame3.png");
    frames[3] = LoadTexture("assets/menu/frame4.png");
    frames[4] = LoadTexture("assets/menu/frame5.png");
    frames[5] = LoadTexture("assets/menu/frame6.png");
    frames[6] = LoadTexture("assets/menu/frame7.png");
    frames[7] = LoadTexture("assets/menu/frame8.png");
    frames[8] = LoadTexture("assets/menu/frame9.png");
}

MenuAction Menu::Update(float dt)
{
    animTimer += dt;

    if (animTimer >= animSpeed)
    {
        animTimer = 0.0f;
        currentFrame++;
        if (currentFrame >= frameCount)
            currentFrame = 0;
    }

    Vector2 mouse = GetMousePosition();

    if (CheckCollisionPointRec(mouse, soloButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return MenuAction::PLAY_SOLO;
    }

    if (CheckCollisionPointRec(mouse, versusButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return MenuAction::PLAY_VERSUS;
    }

    if (CheckCollisionPointRec(mouse, quitButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return MenuAction::QUIT;
    }

    return MenuAction::NONE;
}

void Menu::Draw()
{
    Rectangle source = { 0, 0, (float)frames[currentFrame].width, (float)frames[currentFrame].height };
    Rectangle dest = { 0, 0, 800, 450 };

    DrawTexturePro(frames[currentFrame], source, dest, { 0, 0 }, 0, WHITE);

    Vector2 mouse = GetMousePosition();

    Color soloColor = CheckCollisionPointRec(mouse, soloButton) ? LIGHTGRAY : WHITE;
    Color versusColor = CheckCollisionPointRec(mouse, versusButton) ? LIGHTGRAY : WHITE;
    Color quitColor = CheckCollisionPointRec(mouse, quitButton) ? LIGHTGRAY : WHITE;

    DrawRectangleRec(soloButton, soloColor);
    DrawRectangleLinesEx(soloButton, 2, BLACK);

    DrawRectangleRec(versusButton, versusColor);
    DrawRectangleLinesEx(versusButton, 2, BLACK);

    DrawRectangleRec(quitButton, quitColor);
    DrawRectangleLinesEx(quitButton, 2, BLACK);

    DrawText("PONG", 315, 70, 50, WHITE);
    DrawText("1 JOUEUR", 330, 188, 25, BLACK);
    DrawText("2 JOUEURS", 325, 268, 25, BLACK);
    DrawText("QUITTER", 340, 348, 25, BLACK);
    
}