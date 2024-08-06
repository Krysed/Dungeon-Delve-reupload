#pragma once
#include "raylib.h"
#include "Enemy.h"

class Prop
{
public:
	Prop() {};
	Prop(Vector2 pos, Texture2D tex);
	~Prop();

	void Render(Vector2 knightPos);
	void setTexture(Texture2D tex);
	void setScale(float scale);

	Rectangle getCollisionRec(Vector2 knightPos);
	Vector2 getWorldPos() { return worldPos; }

protected:
	Texture2D texture{};
	Vector2 worldPos{};
	float scale{ 4.f };
};

