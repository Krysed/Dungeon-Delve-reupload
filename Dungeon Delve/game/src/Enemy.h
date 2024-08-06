#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "Character.h"
#include "BaseCharacter.h"

class Enemy : public BaseCharacter
{
private:
	Character* target;
	float damagePerSec{ 10.f };
	float radius{ 25.f };
	Vector2 startPostion{};
public:

	Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
	void setTarget(Character* character);
	virtual void tick(float deltaTime)override;
	void tick(float deltaTime, Character* character);
	virtual Vector2 getScreenPos()override;
	void setWorldPos(float x, float y);
	Vector2 getStartPosition();
};
#endif
