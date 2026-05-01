#pragma once
#include "raylib.h"

class Paddle {
public:

	Vector2 pos;
	float l;
	Texture2D paddle;
	float speed = 420.0f;

	Paddle(Vector2 StartPos, float longueur);

	void UpdateAI(float dt, float targetY);
	void UpdatePlayer2(float dt);
	void Update(float dt);
	void Draw();

};