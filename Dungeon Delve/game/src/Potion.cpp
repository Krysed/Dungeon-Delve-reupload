#pragma once
#include "Potion.h"

Potion::Potion(Vector2 pos, Texture2D tex):
	Item(pos,tex){}

Potion::~Potion() {}

void Potion::interact(Character* player)
{
	if (getConsumed())return;
	player->heal(healAmount);
	setConsumed(true);
}
