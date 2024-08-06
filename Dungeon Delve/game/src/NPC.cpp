#include "NPC.h"

NPC::NPC() {}

NPC::~NPC() {}

NPC::NPC(Vector2 pos, Texture2D tex) :
	Prop(pos,tex)
{
	worldPos = pos;
	texture = tex;
}

void NPC::Render(Vector2 knightPos)
{
	Vector2 screenPos{ Vector2Subtract(worldPos, knightPos) };
	DrawTextureEx(texture, screenPos, 0.f, 4.f, WHITE);
}
