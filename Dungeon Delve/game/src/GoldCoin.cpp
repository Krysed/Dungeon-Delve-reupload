#include "GoldCoin.h"

GoldCoin::GoldCoin(Vector2 pos, Texture2D texture):Item(pos,texture) {}

GoldCoin::~GoldCoin() {}

void GoldCoin::setGoldAmount(int gold)
{
	goldAmount = gold;
}

int GoldCoin::getGoldAmount()
{
	return goldAmount;
}

void GoldCoin::increaseGoldCount()
{
	if (getConsumed())return;
	Character::goldAmount+=5;
	setConsumed(true);
}

void GoldCoin::interact(Character* player)
{
	increaseGoldCount();
}
