/***************************************************************************************************
*   Raylib - Advance Game template
*
*   Ending Screen Functions Definitions (Init, Update, Draw, Unload).
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5).
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*        wrote the original software. If you use this software in a product, an acknowledgment
*        in the product documentation would be appreciated but is not required.
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*        as being the original software.
*     3. This notice may not be removed or altered from any source distribution.
***************************************************************************************************/

#include "raylib.h"
#include "screens.h"

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
// Ending Screen Functions Definition
//--------------------------------------------------------------------------------------------------


// Ending Screen Initialization logic
void InitEndingScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    image = LoadImage("resources/screens/menu.png");
    ImageResize(&image, 800, 600);
    background = LoadTextureFromImage(image);
}


// Ending Screen Update logic
void UpdateEndingScreen(void)
{
    //Fullscreen
    if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER))
    {
        ToggleFullscreen();
    }

    //Draw background
    DrawTexture(background, 0, 0, WHITE);
    
    //Draw buttons
    DrawRectangle(290, 200, 220, 50, DARKGRAY);
    DrawText("RESTART", 352, 215, 20, WHITE);

    DrawRectangle(290, 270, 220, 50, DARKGRAY);
    DrawText("MAIN MENU", 343, 285, 20, WHITE);

    DrawRectangle(290, 340, 220, 50, DARKGRAY);
    DrawText("EXIT", 375, 355, 20, WHITE);
    
//----------------------------------------------------------------------------------
// Logic of button
//----------------------------------------------------------------------------------
    Rectangle buttonRestart = { 290, 185, 220, 50 };
    Rectangle buttonMenu = { 290, 255, 220, 50 };
    Rectangle buttonExit = { 290, 325, 220, 50 };

    if (CheckCollisionPointRec(GetMousePosition(), buttonRestart))
    {
        //Change cursor on button
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        //Animation
        if (isIncreasing)
        {
            alpha += 0.02f;
            if (alpha > 1.0f)
            {
                alpha = 1.0f;
                isIncreasing = false;
            }
        }
        else
        {
            alpha -= 0.02f;
            if (alpha < 0.0f)
            {
                alpha = 0.0f;
                isIncreasing = true;
            }
        }
        Color rectColor = { 79, 79, 79, (unsigned char)(alpha * 255) };
        DrawRectangle(290, 200, 220, 50, rectColor);
    }
    else if (CheckCollisionPointRec(GetMousePosition(), buttonMenu))
    {
        //Change cursor on button
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        //Animation
        if (isIncreasing)
        {
            alpha += 0.02f;
            if (alpha > 1.0f)
            {
                alpha = 1.0f;
                isIncreasing = false;
            }
        }
        else
        {
            alpha -= 0.02f;
            if (alpha < 0.0f)
            {
                alpha = 0.0f;
                isIncreasing = true;
            }
        }
        Color rectColor = { 79, 79, 79, (unsigned char)(alpha * 255) };
        DrawRectangle(290, 270, 220, 50, rectColor);
    }
    else if (CheckCollisionPointRec(GetMousePosition(), buttonExit))
    {
        //Change cursor on button
        //Animation
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        if (isIncreasing)
        {
            alpha += 0.02f;
            if (alpha > 1.0f)
            {
                alpha = 1.0f;
                isIncreasing = false;
            }
        }
        else
        {
            alpha -= 0.02f;
            if (alpha < 0.0f)
            {
                alpha = 0.0f;
                isIncreasing = true;
            }
        }
        Color rectColor = { 79, 79, 79, (unsigned char)(alpha * 255) };
        DrawRectangle(290, 340, 220, 50, rectColor);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    //Button forwards
    if (CheckCollisionPointRec(GetMousePosition(), buttonRestart) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // Set finishScreen to the ID of the screen you want to switch to
        finishScreen = 2;
    }
    if (CheckCollisionPointRec(GetMousePosition(), buttonMenu) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // Set finishScreen to the ID of the screen you want to switch to
        finishScreen = 1;
    }
    if (CheckCollisionPointRec(GetMousePosition(), buttonExit) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // Set finishScreen to the ID of the screen you want to switch to
        CloseWindow();
    }
}


// Ending Screen Draw logic
void DrawEndingScreen(void)
{
    // TODO: Draw ENDING screen here!
}

// Ending Screen Unload logic
void UnloadEndingScreen(void)
{
    // TODO: Unload ENDING screen variables here!
}

// Ending Screen should finish?
int FinishEndingScreen(void)
{
    return finishScreen;
}