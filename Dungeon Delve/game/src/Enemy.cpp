#pragma once
#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    startPostion = pos;
    worldPosition = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    target = {};
    width = texture.width;
	height = texture.height;
    speed = 1.5f;
}

void Enemy::setTarget(Character* character)
{
    target = character;
}

void Enemy::tick(float deltaTime, Character* character)
{
    if (!getAlive())return;

    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity) < radius) velocity = {};
    BaseCharacter::tick(deltaTime);
    if (Vector2Distance(getScreenPos(), character->getScreenPos()) < 300)
    {
        texture = run;        
        setTarget(character);
    }
    else
    {
        texture = idle;
        undoMovement();
    }
    if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }

    ////updating the change in texture
    Rectangle source{ frame * width / 6.f,0.f,rightLeft * width / 6.f,height };
    Rectangle destination{ getScreenPos().x,getScreenPos().y,4.0f * width / 6.f,4.0f * height };
    DrawTexturePro(texture, source, destination, Vector2{}, 0.f, WHITE);
}

void Enemy::tick(float deltaTime)
{
    if (!getAlive())return;

    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity) < radius) velocity = {};
    BaseCharacter::tick(deltaTime);

    if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPosition, target->getWorldPos());
}

void Enemy::setWorldPos(float x,float y)
{
    worldPosition.x = x;
    worldPosition.y = y;
}

Vector2 Enemy::getStartPosition()
{
    return startPostion;
}
