#pragma once

#include "BaseCharacter.h"
#include "raymath.h"
BaseCharacter::BaseCharacter() {}

Vector2 BaseCharacter::getWorldPos()
{
    return worldPosition;
}

void BaseCharacter::undoMovement()
{
    worldPosition = worldPositionLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle
    {
        getScreenPos().x,
        getScreenPos().y,
        (width/6) * scale,
        height * scale
    };
}

void BaseCharacter::tick(float deltaTime)
{
    worldPositionLastFrame = worldPosition;

    //update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames) frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        worldPosition = Vector2Add(worldPosition, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};
}