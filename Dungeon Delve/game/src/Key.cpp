#include "Key.h"
#pragma once

Key::Key(Vector2 pos, Texture2D texture):Item(pos,texture) {}

Key::~Key(){}

void Key::interact(Character* player)
{
	if (getConsumed())return;
	Character::key++;
	setConsumed(true);
}
