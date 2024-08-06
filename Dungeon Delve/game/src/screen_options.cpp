#include "raylib.h"
#include "screens.h"
#include <string.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
static Image image;
static Texture2D background;
static float alpha = 0.0f;
static bool isIncreasing = true;
char name[10] = "Player";

//----------------------------------------------------------------------------------
// Options Screen Functions Definition
//----------------------------------------------------------------------------------

// Options Screen Initialization logic
void InitOptionsScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    image = LoadImage("resources/screens/menu.png");
    ImageResize(&image, 800, 600);
    background = LoadTextureFromImage(image);
}

// Options Screen Update logic
void UpdateOptionsScreen(void)
{
    //Fullscreen
    if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER))
    {
        ToggleFullscreen();
    }

    //Draw background
    DrawTextureEx(background, { 0, 0 }, 0, 1.f, WHITE);

    //Draw buttons
    DrawRectangle(290, 200, 220, 50, DARKGRAY);
    DrawText("PLAY GAME", 340, 215, 20, WHITE);

    DrawRectangle(290, 270, 220, 50, DARKGRAY);
    DrawText("SCORE BOARD", 327, 285, 20, WHITE);

    DrawRectangle(290, 340, 220, 50, DARKGRAY);
    DrawText("EXIT", 375, 355, 20, WHITE);
    
    //----------------------------------------------------------------------------------
    // Logic of button
    //----------------------------------------------------------------------------------

    Rectangle buttonPlay = { 290, 185, 220, 50 };
    Rectangle buttonScore = { 290, 255, 220, 50 };
    Rectangle buttonExit = { 290, 325, 220, 50 };

    if (CheckCollisionPointRec(GetMousePosition(), buttonPlay))
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
    else if (CheckCollisionPointRec(GetMousePosition(), buttonScore))
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
    if (CheckCollisionPointRec(GetMousePosition(), buttonPlay) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // Set finishScreen to the ID of the screen you want to switch to
        finishScreen = 1;
    }
    if (CheckCollisionPointRec(GetMousePosition(), buttonScore) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // Set finishScreen to the ID of the screen you want to switch to
        finishScreen = 2;
    }
    if (CheckCollisionPointRec(GetMousePosition(), buttonExit) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // Set finishScreen to the ID of the screen you want to switch to
        CloseWindow();
    }

    //------------------------------------------------------------------------
    // NAME FIELD
    //------------------------------------------------------------------------
     
    //Draw name field
    DrawText("Enter your name:", 280, 100, 20, WHITE);
    DrawRectangle(280, 130, 240, 50, DARKGRAY);
    DrawRectangleLines(280, 130, 240, 50, WHITE);
    DrawText(name, 290, 140, 40, WHITE);

    //Logic of writing
    int key = GetCharPressed();  // Sprawdza, czy klawisz zosta³ wciœniêty
    if (key > 0 && strlen(name) < 10)  // Jeœli klawisz zosta³ wciœniêty i imiê nie jest za d³ugie
    {
        name[strlen(name)] = (char)key;  // Dodaj wprowadzon¹ literê na koñcu ³añcucha
    }
    if (IsKeyPressed(KEY_BACKSPACE) && strlen(name) > 0)  // Jeœli wciœniêto klawisz BACKSPACE i imiê nie jest puste
    {
        name[strlen(name) - 1] = '\0';  // Usuñ ostatni¹ literê z ³añcucha
    }
}

// Options Screen Draw logic
void DrawOptionsScreen(void)
{
    // TODO: Draw OPTIONS screen here!
}

// Options Screen Unload logic
void UnloadOptionsScreen(void)
{
    // TODO: Unload OPTIONS screen variables here!
}

// Options Screen should finish?
int FinishOptionsScreen(void)
{
    return finishScreen;
}
