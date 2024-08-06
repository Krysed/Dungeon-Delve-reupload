#pragma once
#include "Item.h"

class HealthIncrease : public Item
{
private:
	float increaseValue = 50.f;

public:
	HealthIncrease(Vector2 pos, Texture2D texture);
	~HealthIncrease();

	virtual void interact(Character* player)override;
};