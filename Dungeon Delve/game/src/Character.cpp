#include "src/Character.h"

Character::Character(int windowWidth, int windowHeight):
    windowWidth(windowWidth),windowHeight(windowHeight)
{
    width = texture.width;// / maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos() 
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.f - scale * (0.5f * width / 6.f),
        static_cast<float>(windowHeight) / 2.f - scale * (0.5f * width / 6.f)
    };
}

void Character::setMaxHealth(float value)
{
    maxHealth += value;
}

void Character::tick(float deltaTime)
{

    if (!getAlive())return;

    if ((IsKeyDown(KEY_A)) || (IsKeyDown(KEY_LEFT))) velocity.x -= 1.0;
    if ((IsKeyDown(KEY_D)) || (IsKeyDown(KEY_RIGHT))) velocity.x += 1.0;
    if ((IsKeyDown(KEY_W)) || (IsKeyDown(KEY_UP))) velocity.y -= 1.0;
    if ((IsKeyDown(KEY_S)) || (IsKeyDown(KEY_DOWN))) velocity.y += 1.0;
    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (rightLeft > 0.f)
    {
        origin = { 0.f,weapon.height * scale };
        //setting weapon offset
        offset = { 35.f,50.f };
        weaponCollisionRec = { getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
    }
    else
    {
        origin = { weapon.width * scale,weapon.height * scale };
        offset = { 25.f,50.f };
        weaponCollisionRec = { getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
    }


    //drawing character
    Rectangle source2{ frame * width / 6.f,0.f,rightLeft * width / 6.f,height };
    Rectangle destination{ getScreenPos().x,getScreenPos().y,4.0f * width / 6.f,4.0f * height };
    DrawTexturePro(texture, source2, destination, Vector2{}, 0.f, WHITE);
    //draw sword
    Rectangle source{ 0.f,0.f,static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height) };
    Rectangle dest{ getScreenPos().x + offset.x ,getScreenPos().y + offset.y, weapon.width * scale,weapon.height * scale };
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);
}

void Character::heal(float amount)
{
    if(health < maxHealth) health += amount;
    if (health > maxHealth) health = maxHealth;
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0.f)
    {
        setAlive(false);
    }
}