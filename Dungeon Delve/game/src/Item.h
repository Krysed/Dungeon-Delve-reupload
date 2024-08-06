#pragma once
#include "Prop.h"

class Item : public Prop
{
private:
	bool consumed = false;
public:
	Item(Vector2 pos, Texture2D texture);
	~Item();

	bool getConsumed();
	void setConsumed(bool status);
	virtual void interact(Character* player) = 0;
};