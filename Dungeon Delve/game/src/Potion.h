#pragma once
#include "Item.h"
#include "Character.h"

class Potion :
    public Item
{
private:
    float healAmount = 25.f;
    
public:
    Potion(Vector2 pos, Texture2D tex);
    ~Potion();

    virtual void interact(Character* player)override;
};

