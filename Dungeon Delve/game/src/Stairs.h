#pragma once

#include "Item.h"

class Stairs : public Item
{
private:
	float increaseValue = 50.f;

public:
	Stairs(Vector2 pos, Texture2D texture);
	~Stairs();

	virtual void interact(Character* player)override;
};