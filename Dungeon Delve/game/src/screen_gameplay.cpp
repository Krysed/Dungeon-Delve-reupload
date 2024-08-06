/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "src/HealthIncrease.h"
#include "src/Character.h"
#include "src/GoldCoin.h"
#include "src/Globals.h"
#include "mapLayouts.h"
#include "src/Potion.h"
#include "src/Stairs.h"
#include "src/Enemy.h"
#include "src/Prop.h"
#include "raymath.h"
#include "screens.h"
#include "src/Key.h"
#include "src/NPC.h"
#include "raylib.h"
#include "fstream"

static int framesCounter = 0;
static int finishScreen = 0;
int Character::experience = 0;
int Character::goldAmount = 0;
int Character::key = 0;
int clickCount = 0;
std::string currentMap;
double startTime = GetTime();
static float alpha = 0.0f;
static bool isIncreasing = true;

void InitGameplayScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    Character::experience = 0;

    // Loading screen
    int screenWidth = 800;
    int screenHeight = 600;
    Rectangle loadBar = { screenWidth / 2 - 100, screenHeight / 2, 0, 20 };
    int progress = 0;

    while (progress < 100)
    {
        progress++;
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("LOADING...", screenWidth / 2 - 50, screenHeight / 2 - 50, 20, WHITE);
        DrawRectangleRec(loadBar, WHITE);
        DrawText(TextFormat("%i%%", progress), screenWidth / 2 - 20, screenHeight / 2 + 20, 20, WHITE);
        EndDrawing();
    }
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    const int windowWidth{ 800 };
    const int windowHeight{ 600 };
    const float mapScale{ 4.0f };

    int mapVar = 0;
    bool isBuying = false;

    //fix sound
    Sound gameMusic = LoadSound(gameplayMusic);
    SetSoundVolume(gameMusic, 0.5f);
    
    // Cutting sound
    Sound cutSound = LoadSound(sound2);
    SetSoundVolume(cutSound, 0.1f);
    
    Sound openSound = LoadSound(sound1);
    SetSoundVolume(openSound, 0.2f);
    
    Sound sprintSound = LoadSound(sound3);
    SetSoundVolume(sprintSound, 0.5f);

    Texture2D map = LoadTexture(baseMap);
    Vector2 mapPosition{ 0.0f,0.0f };
    Character player{ windowWidth,windowHeight };

    //populating level with props
    std::vector<Prop> props{};
    std::cout << mapLayout->length() << "\n\n";
    for (int i = 0; i < numOfProps; i++)
    {
        for (int j = 0; j < numOfProps; j++)
        {
            if (mapLayout[i][j] == ' ')continue;
            else if (mapLayout[i][j] == 'x')props.push_back(Prop{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture(rockTexture) });
            else if (mapLayout[i][j] == 'o')props.push_back(Prop{ Vector2{float(j) * 85,float(i) * 85 }, LoadTexture(logTexture) });
            else if (mapLayout[i][j] == 's')props.push_back(Prop{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture(signTexture) });
            else if (mapLayout[i][j] == 'b')props.push_back(Prop{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture(bushTexture) });
        }
    }

    std::vector<Prop>dungeonProps{};
    for (int i = 0; i < numOfProps; i++)

    {
        for (int j = 0; j < numOfProps; j++)
        {
            if (mapDungeonLayout[i][j] == ' ')continue;
            else if (mapDungeonLayout[i][j] == 'w')dungeonProps.push_back(Prop{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture(wall1Texture) });
            else if (mapDungeonLayout[i][j] == 'x')dungeonProps.push_back(Prop{ Vector2{float(j) * 85,float(i) * 85 }, LoadTexture(wall2Texture) });
            else if (mapDungeonLayout[i][j] == 's')dungeonProps.push_back(Prop{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture(wall3Texture) });
            else if (mapDungeonLayout[i][j] == 'b')dungeonProps.push_back(Prop{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture(rockTexture) });
        }
    }

    std::vector<Prop>currentProps = props;

    //Enemies
    std::vector<Enemy> enemiesArray;
    for (int i = 0; i < numOfProps; i++)
    {
        for (int j = 0; j < numOfProps; j++)
        {
            if (mapLayoutEnemies[i][j] == ' ')continue;
            else if (mapLayoutEnemies[i][j] == 'x')enemiesArray.push_back(Enemy{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture(goblinIdleTexture),LoadTexture(goblinRunTexture) });
            else if (mapLayoutEnemies[i][j] == 'o')enemiesArray.push_back(Enemy{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture(slimeIdleTexture),LoadTexture(slimeRunTexture) });
            else if (mapLayoutEnemies[i][j] == 's')enemiesArray.push_back(Enemy{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture(skeletonIdleTexture),LoadTexture(skeletonRunTexture) });
        }
    }

    std::vector<Enemy*> enemies;
    for (int i = 0; i < enemiesArray.size(); i++) {
        enemies.push_back(&enemiesArray[i]);
        enemies[i]->setSpeed(3.f);
    }

    Potion pot(Vector2{600.f,2200.f}, LoadTexture(potionTexture));

    GoldCoin gold(Vector2{ 550.f,500.f }, LoadTexture(coinTexture));
    GoldCoin gold2(Vector2{ 2000.f,700.f }, LoadTexture(coinTexture));
    GoldCoin gold3(Vector2{ 800.f,2200.f }, LoadTexture(coinTexture));
    GoldCoin gold4(Vector2{ 600.f,1000.f }, LoadTexture(coinTexture));
    GoldCoin gold5(Vector2{ 600.f,2800.f }, LoadTexture(coinTexture));
    
    Key key(Vector2{ 800.f,1200.f }, LoadTexture(keyTexture));
    Key key2(Vector2{ 2400.f,800.f }, LoadTexture(keyTexture));
    
    HealthIncrease health(Vector2{ 1000.f,550.f }, LoadTexture(healthTexture));
    
    Stairs stairs(Vector2{ 1400.f,850.f }, LoadTexture(stairLockedTexture));
    Stairs stairs2(Vector2{ 2400.f,2000.f }, LoadTexture(stairLockedTexture));
    
    NPC npc(Vector2{ 400.f,550.f }, LoadTexture(npcTexture));


    for (auto enemy : enemies)
    {
        enemy->setTarget(&player);
    }

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP) || IsKeyPressed(KEY_ESCAPE))
        {
            finishScreen = 1;
        }
        //Fullscreen
        if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER))
        {
            ToggleFullscreen();
            Sound fullscreen = LoadSound(sound4);
            SetMusicVolume(music, 0.1f);
            PlaySound(fullscreen);
        }

        while (!IsSoundPlaying(gameMusic)) 
        {
            PlaySound(gameMusic);
        }

        //stairs
        if (IsKeyPressed(KEY_E) && CheckCollisionRecs(stairs.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))
        {
            if(mapVar == 0){
                if (stairs.getConsumed()) {
                    map = LoadTexture(dungeonMap);
                    currentMap = dungeonMap;
                    currentProps = dungeonProps;
                    mapVar = 1;
                    for (auto& prop : currentProps)prop.setScale(5.3f);
                    for (auto& enemy : enemies) {
                        enemy->setWorldPos(enemy->getStartPosition().x,enemy->getStartPosition().y);
                        enemy->setAlive(true);
                    }
                    // Enter dungeon sound
                    PlaySound(openSound);
                }
            }
            else if (mapVar == 1) {
                if (stairs.getConsumed()) {
                    map = LoadTexture(baseMap);
                    currentMap = baseMap;
                    currentProps = props;
                    mapVar = 0;
                }
            }
            if (Character::key > 0 && stairs.getConsumed() == false) {
                Character::key--;
                stairs.setTexture(LoadTexture(stairTexture));
                stairs.setConsumed(true);

            }
        }

        if (IsKeyPressed(KEY_E) && CheckCollisionRecs(stairs2.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))
        {
            if(mapVar == 0){
                if (stairs2.getConsumed()) {
                    map = LoadTexture(dungeonMap);
                    currentMap = dungeonMap;
                    currentProps = dungeonProps;
                    mapVar = 1;
                    for (auto& prop : currentProps)prop.setScale(5.3f);
                    for (auto& enemy : enemies) {
                        enemy->setWorldPos(enemy->getStartPosition().x,enemy->getStartPosition().y);
                        enemy->setAlive(true);
                    }

                    // Enter dungeon sound
                    PlaySound(openSound);
                }
            }
            else if (mapVar == 1) {
                if (stairs2.getConsumed()) {
                    map = LoadTexture(baseMap);
                    currentMap = baseMap;
                    currentProps = props;
                    mapVar = 0;
                }
            }
            if (Character::key > 0 && stairs2.getConsumed() == false) {
                Character::key--;
                stairs2.setTexture(LoadTexture(stairTexture));
                stairs2.setConsumed(true);

            }
        }
        mapPosition = Vector2Scale(player.getWorldPos(), -1.f);

        //Drawing map
        DrawTextureEx(map, mapPosition, 0.0f, mapScale, WHITE);
        
        stairs.Render(player.getWorldPos());
        stairs2.Render(player.getWorldPos());
        player.tick(GetFrameTime());

        npc.Render(player.getWorldPos());
        
        if (CheckCollisionRecs(npc.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))
        {
            isBuying = true;
        }
        else
        {
            isBuying = false;
        }

        if (isBuying) 
        {
            DrawRectangle(45.f, windowHeight / 2 + 45, 720, 65, BEIGE);
            DrawText("Do you want to buy health potion for 5 gold?    Press Y",50.f, windowHeight /2+ 50, 25, YELLOW);
            DrawText("Do you want to buy health increase for 10 gold? Press E",50.f, windowHeight /2 +80, 25, YELLOW);
            if (IsKeyPressed(KEY_Y) && Character::goldAmount >= 5) {
                player.heal(20);
                Character::goldAmount -= 5;
            }            
            if (IsKeyPressed(KEY_E) && Character::goldAmount >= 10) {
                player.setMaxHealth(50);
                player.heal(50);
                Character::goldAmount -= 10;
            }
        }

        if(!pot.getConsumed())pot.Render(player.getWorldPos());
        if (!gold.getConsumed())gold.Render(player.getWorldPos());
        if (!gold2.getConsumed())gold2.Render(player.getWorldPos());
        if (!gold3.getConsumed())gold3.Render(player.getWorldPos());
        if (!gold4.getConsumed())gold4.Render(player.getWorldPos());
        if (!gold5.getConsumed())gold5.Render(player.getWorldPos());
        if (!key.getConsumed())key.Render(player.getWorldPos());
        if (!key2.getConsumed())key2.Render(player.getWorldPos());
        if (!health.getConsumed())health.Render(player.getWorldPos());

        for (auto prop : currentProps)
        {
            prop.Render(player.getWorldPos());
        }

        if (!player.getAlive()) 
        {
            DrawRectangle(170, 120, 465, 370, BLACK);
            DrawRectangle(180, 130, 445, 350, GRAY);
            DrawText("Game Over", 300.f, 250.f, 40, RED);
            DrawText(TextFormat("Final Experience: %d", Character::experience), 210.f, 300.f, 40, LIGHTGRAY);

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
            DrawText("Press ESC to continue", 280.f, 410.f, 20, WHITE);
            Color rectColor = { 130, 130, 130, (unsigned char)(alpha * 255) };
            DrawRectangle(180, 400, 445, 50, rectColor);
            EndDrawing();
            continue;
        }

        else
        {
            //write Player character stats to screen
            std::string playerHealth = "Health:";
            std::string playerExperience = "Experience:";
            std::string playerGold = "Gold:";
            std::string playerKey = "Keys:";



            playerHealth.append(std::to_string(player.getHealth()), 0, 5);
            playerExperience.append(std::to_string(Character::experience), 0, 5);
            playerGold.append(std::to_string(Character::goldAmount), 0, 5);
            playerKey.append(std::to_string(Character::key), 0, 5);

            DrawText(playerHealth.c_str(), 500, 22.f, 40, RED);
            DrawText(playerExperience.c_str(), 100.f, 72.f, 40, LIGHTGRAY);
            DrawText(playerGold.c_str(), 100.f, 22.f, 40, GOLD);
            if (Character::key > 0)
            {
                DrawText(playerKey.c_str(), 550.f, 82.f, 40, LIGHTGRAY);
            }
        }

        //checking player-map bounds
        if (
            player.getWorldPos().x < 0.f ||
            player.getWorldPos().y < 0.f ||
            player.getWorldPos().x + windowWidth > map.width * mapScale ||
            player.getWorldPos().y + windowHeight > map.height * mapScale
            ) {
            player.undoMovement();
        }

        //checking player-prop collision
        for (auto prop : currentProps)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))
            {
                player.undoMovement();
            }
            if (CheckCollisionRecs(pot.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))
            {
                pot.interact(&player);
            }
            
            if (CheckCollisionRecs(gold.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))gold.interact(&player);
            if (CheckCollisionRecs(gold2.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))gold2.interact(&player);
            if (CheckCollisionRecs(gold3.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))gold3.interact(&player);
            if (CheckCollisionRecs(gold4.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))gold4.interact(&player);

            if (CheckCollisionRecs(key.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))
            {
                key.interact(&player);
            }            
            if (CheckCollisionRecs(key2.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))
            {
                key2.interact(&player);
            }
            if (CheckCollisionRecs(health.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))
            {
                health.interact(&player);
            }
        }
        
        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime(),&player);
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), player.getWeaponCollisionRec()))
                {
                    if (enemy->getAlive() == true) {
                        Character::experience++;
                        PlaySound(cutSound);
                        enemy->setAlive(false);
                    }
                }
            }
        }

        DrawText(("FPS: " + std::to_string(GetFPS())).c_str(), 20, 575, 20, WHITE);

        double elapsedTime = GetTime() - startTime;
        int minutes = (int)(elapsedTime / 60.0);
        int seconds = (int)(elapsedTime) % 60;


        if(IsKeyDown(KEY_LEFT_SHIFT))
        {
            player.setSpeed(player.getSprintSpeed());
            while(!IsSoundPlaying(sprintSound))PlaySound(sprintSound);
        }
        else 
        {
            player.setSpeed(player.getBaseSpeed());
            if(IsSoundPlaying(sprintSound))StopSound(sprintSound);
        }
        UnloadGameplayScreen();
    }
    UnloadSound(gameMusic);

    // Saving final experience to file
    std::ofstream outfile;
    outfile.open ("./game/experience.txt", std::ios::app);
    outfile << Character::experience << " - "<< name << std::endl;
    outfile.close();

    Character::key = 0;
    Character::goldAmount = 0;
    Character::experience = 0;
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{

}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    EndDrawing();
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}