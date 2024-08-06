#pragma once
#include "Item.h"
#include "raylib.h"


Item::Item(Vector2 pos, Texture2D tex) :Prop(pos,tex) {}

Item::~Item() {}

bool Item::getConsumed()
{
	return consumed;
}

void Item::setConsumed(bool status)
{
	consumed = status;
}
