/***************************************************************************************************
*   Raylib - Advance Game template.
*
*   Title Screen Functions Definitions (Init, Update, Draw, Unload).
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5).
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*     3. This notice may not be removed or altered from any source distribution.
***************************************************************************************************/

#include "raylib.h"
#include "screens.h"
#include <external/stb_image.h>

//--------------------------------------------------------------------------------------------------
// Module Variables Definition (local)
//--------------------------------------------------------------------------------------------------

static int framesCounter = 0;
static int finishScreen = 0;
static Image image;
static Texture2D background;
static float alpha = 0.0f;
static bool isIncreasing = true;

//--------------------------------------------------------------------------------------------------
// Title Screen Functions Definition
//--------------------------------------------------------------------------------------------------

// Title Screen Initialization logic
void InitTitleScreen(void)
{
    // TODO: Initialize TITLE screen variables here!
    SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    framesCounter = 0;
    finishScreen = 0;
    image = LoadImage("resources/screens/DungeonDelve.png");
    ImageResize(&image, 800, 600);
    background = LoadTextureFromImage(image);
}

// Title Screen Update logic
void UpdateTitleScreen(void)
{
    //Fullscreen
    if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER))
    {
        ToggleFullscreen();
    }
    // TODO: Update TITLE screen variables here!

    // Press enter or tap to change to GAMEPLAY screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1; // OPTIONS
        //finishScreen = 2; // GAMEPLAY
        PlaySound(fxCoin);
    }

}

// Title Screen Draw logic
void DrawTitleScreen(void)
{
    // TODO: Draw TITLE screen here!
    DrawTexture(background, 0, 0, WHITE);
    Vector2 pos = { 20, 10 };
    DrawText("PRESS ENTER TO START", 268, 27, 20, WHITE);

    //Animation of text
    if (isIncreasing)
    {
        alpha += 0.01f;
        if (alpha > 1.0f)
        {
            alpha = 1.0f;
            isIncreasing = false;
        }
    }
    else
    {
        alpha -= 0.01f;
        if (alpha < 0.0f)
        {
            alpha = 0.0f;
            isIncreasing = true;
        }
    }

    Color rectColor = { 0, 0, 0, (unsigned char)(alpha * 255) };
    DrawRectangle(0, 0, GetScreenWidth(), 43, rectColor);
}

// Title Screen Unload logic
void UnloadTitleScreen(void)
{
    // TODO: Unload TITLE screen variables here!
}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finishScreen;
}