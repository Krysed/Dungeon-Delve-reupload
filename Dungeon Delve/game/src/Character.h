#pragma once
#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
private:
	int windowWidth{};
	int windowHeight{};
	float maxHealth = 100.f;
	float health{ 100.f };

	Texture2D weapon{LoadTexture("resources/characters/sword_loot.png")};
	Rectangle weaponCollisionRec{};

public:
	static int experience;
	static int goldAmount;
	static int key;

	Character(int windowWidth, int windowHeight);

	virtual void tick(float deltaTime) override;
	virtual Vector2 getScreenPos() override;
	Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }
	void setMaxHealth(float value);
	float getHealth() const { return health; }
	void heal(float amount);
	void takeDamage(float damage);
	void setWeaponTexture(Texture2D newWeapon) { weapon = newWeapon; }
};