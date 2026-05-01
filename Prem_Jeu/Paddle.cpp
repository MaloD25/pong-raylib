#include "Paddle.h"


Paddle::Paddle(Vector2 StartPos, float longueur)
	: pos(StartPos), l(longueur)
{
	paddle = LoadTexture("assets/Paddle.png");
}

void Paddle::Update(float dt) {
	
	if (IsKeyDown(KEY_UP)) pos.y -= dt * speed;
	if (IsKeyDown(KEY_DOWN)) pos.y += dt * speed;

	if (pos.y < 0) pos.y = 0;
	if (pos.y + l > 450) pos.y = 450 - l;
}

void Paddle::UpdateAI(float dt, float targetY)
{
	float centerY = pos.y + l / 2.0f;

	if (centerY < targetY - 60.0f)
	{
		pos.y += dt * speed;
	}
	else if (centerY > targetY + 60.0f)
	{
		pos.y -= dt * speed;
	}

	if (pos.y < 0) pos.y = 0;
	if (pos.y + l > 450) pos.y = 450 - l;
}

void Paddle::UpdatePlayer2(float dt)
{
	if (IsKeyDown(KEY_Q)) pos.y -= dt * speed;
	if (IsKeyDown(KEY_A)) pos.y += dt * speed;

	if (pos.y < 0) pos.y = 0;
	if (pos.y + l > 450) pos.y = 450 - l;
}

void Paddle::Draw()
{
	Rectangle source = { 0, 0, paddle.width, paddle.height };
	Rectangle dest = { pos.x, pos.y, l/4, l };

	DrawTexturePro(paddle, source, dest, { 0,0 }, 0, RED);
}