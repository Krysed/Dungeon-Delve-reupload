#pragma once
#include "Item.h"

class Key : public Item
{
private:
	
public:
	Key(Vector2 pos, Texture2D texture);
	~Key();

	virtual void interact(Character* player)override;
};