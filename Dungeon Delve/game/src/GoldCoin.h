#pragma once
#include "Item.h"

class GoldCoin : public Item
{
private:
	Character* player;
	int goldAmount = 5;

public:
	GoldCoin(Vector2 pos, Texture2D texture);
	~GoldCoin();

	void setGoldAmount(int gold);
	int getGoldAmount();
	void increaseGoldCount();
	virtual void interact(Character* player) override;
};
