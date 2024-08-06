#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"
class BaseCharacter
{
public:
	BaseCharacter();
	void undoMovement();
	virtual void tick(float deltaTime);

	virtual Vector2 getScreenPos() = 0;
	Vector2 getWorldPos();
	Rectangle getCollisionRec();
	bool getAlive() const { return alive; }
	float getSprintSpeed() const { return sprintSpeed; }
	float getBaseSpeed() const { return baseSpeed; }
	float getSpeed() const { return speed; }
	
	void setAlive(bool isAlive) { alive = isAlive; }
	void setSpeed(float spd) { speed = spd; }
protected:
	Texture2D texture{ LoadTexture("resources/characters/knight_idle_spritesheet.png") };
	Texture2D idle{ LoadTexture("resources/characters/knight_idle_spritesheet.png") };
	Texture2D run{ LoadTexture("resources/characters/knight_run_spritesheet.png") };
	Vector2 screenPosition{};
	Vector2 worldPosition{};
	Vector2 worldPositionLastFrame{};
	Vector2 velocity{};

	float rightLeft{ 1.f };
	float runningTime{};
	float speed{ 4.f };
	float sprintSpeed{ 6.f };
	int frame{};

	float scale{ 4.f };
	float height{};
	float width{};

	const int maxFrames{ 6 };
	const float updateTime{ 1.f / 12.f };
	const float baseSpeed{ 4.f };
private:
	bool alive = true;
};

#endif