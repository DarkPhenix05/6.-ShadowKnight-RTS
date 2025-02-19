#include <iostream>
#include "raylib.h"
#include "Character.h"
#include "PathFinder.hpp"
#include "Map.hpp"
#include "string"
#include "TroopManager.h"
#pragma once

/*==================================NOTES================================================================================
CONTROLS:
    WASD: MOVE VEW CAMERA

    Y: CAMERA FOLLOW TROOP

    MOUSE:
        >L-CLICK: SELECT TROPE (ON MAP VEW)
        >R_CLICK: SELECT POS TO MOVE OR DO ACTION(ON MAP VEW, ONLY MOVE ON SERVICE)

RULES:
    ADDING TROOPS:
        >UNSELECT CURRENT CHARACTER BY CLICKING ON AN NON-USED FIELD.
        >YOU CAN ADD KNIGHTS, BUILDERS AND DEFENDERS, ITCH WITH THEIR OWN SPRITES AND ATTRIBUTES.

    TAKING ACTION:
        >SELECT A CHARACTER WITH LEFT-CLICK ON THE WORLD MAP, AND WHEN IT LIGHTS UP THE BUTTONS WILL CHANGE TO THE
            ACTIONS, SELECT THE CELL TO DO ACTION AT, WITH RIGHT CLICK; AND PRESS "MOVE".

UI:
    WALLS:
        >MARKED WITH BLUE CELLS
    PATHS:
        >MARKED WITH GREEN CELLS
    WORLD OR MINI MAP:
        >FOUND ON THE LEFT UPPER PORTION OF THE SCREEN, SHOWS THE HOLE AREA OR WORLD.
    ZOOM MAP:
        >FOUND ON THE RIGHT PORTION OF THE SCREEN, BEING BIGGER AND ABLE TO SEE WHAT IS BEING DONE IN THE GAME
            WITH BETTER DETAIL.
    BUTTONS:
        >FOUND ON THE LEFT LOWER PORTION, SHOWING THEIR STATE WITH COLOR CHANGES. SUCH AS HOVER, PRESS & INACTIVE.

PROGRAM:
    PATH FINDER:
        >USES THE "A*" METHOD, TO GENERATE PATH FINDING BEHAVIOR.
        >UTILISES A "MAP" OF STRINGS, FOR OPTIMISATION.
    RENDER:
        >USES "RAY-LIB", TO GENERATE THE VISUAL INTERFACE.
    RIGHTS AND APA:
        >READ ME
 ==========================================================THANKS=======================================================*/

void Draw();
int TurnToBaseX(int base, int num);

PathFinder* pathFinder = new PathFinder(35, 35, 25, 25);
Map* GlobalMap = new Map();
TroopManager* troop_manager = new TroopManager();

Button* BT_ADDKNIGHT;
Button* BT_ADDDEFENDER;
Button* BT_ADDBUILDER;

int main()
{
    BT_ADDKNIGHT = new Button(5,205,90,45,"ADD KNIGHT",20, GRAY,BLACK,
        LIGHTGRAY,BLACK,WHITE,GRAY,RED,BLACK);

    BT_ADDDEFENDER = new Button(105,205,90,45,"ADD DEFENDER",20, GRAY,BLACK,
        LIGHTGRAY,BLACK,WHITE,GRAY,RED,BLACK);

    BT_ADDBUILDER = new Button(5,255,90,45,"ADD BUILDER",20, GRAY,BLACK,
        LIGHTGRAY,BLACK,WHITE,GRAY,RED,BLACK);
    
    const Color blue = { 44, 44, 125, 255 };

    InitWindow(600, 400, "Tragones y Masmorras");

    Vector2 camPos = { 0,0 };

    SetTargetFPS(60);


    Camera2D cam1;

    
    cam1.target = Vector2{ 0,0 };
    
    
    cam1.offset = { 0,0 };
    cam1.rotation = 0;
    cam1.zoom = .5f;

    Camera2D cam2;

    cam2.target = { 0,0 };
    cam2.offset = { 0,0 };
    cam2.rotation = 0;
    cam2.zoom = 2;

    RenderTexture screen1 = LoadRenderTexture(200, 200);
    RenderTexture screen2 = LoadRenderTexture(600, 400);

    Rectangle splitScreen = { 0,0,(float)screen1.texture.width,-(float)screen1.texture.height };
    Rectangle splitScreen2 = { 0,0,600,-400 };

    bool Follow = false;
    Vector2 savedPos = { 0, 0 };

    GlobalMap->GenerateGrid(18, 18, 25, 25, 20);
    int cellW = 25;
    int cellH = 25;

    int CurSize = 10;

    pathFinder->Tiles = GlobalMap->GetMap();


    // ======UPDATE=====================================================================================================
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();


        if (IsKeyPressed(KEY_Y))
        {
            Follow = !Follow;
        }

        if (Follow && troop_manager->GetCurrentCharacter())
        {
            camPos = { troop_manager->GetCurrentCharacter()->GetPos().x - 150/cam2.zoom, troop_manager->GetCurrentCharacter()->GetPos().y - 150/cam2.zoom};
        }
        else
        {
            if (IsKeyDown(KEY_W))
                camPos.y -= 1;
            else if (IsKeyDown(KEY_S))
                camPos.y += 1;
            else if (IsKeyDown(KEY_A))
                camPos.x -= 1;
            else if (IsKeyDown(KEY_D))
                camPos.x += 1;

            Follow = false;
        }

        cam2.target = camPos;

        Vector2 mpos = GetScreenToWorld2D(GetMousePosition(), cam1);

        if (GetMousePosition().x < 200 && GetMousePosition().y < 200)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            {
                savedPos.x = int(round(mpos.x / cellW)) * cellW + (cellW /2) - (CurSize/2);
                savedPos.y = int(round(mpos.y / cellH)) * cellH + (cellH/2) - (CurSize/2);
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                troop_manager->FindCharacterInPos(GetMousePosition(), cellW);
            }
        }

        if (troop_manager->GetCurrentCharacter())
        {
            if (troop_manager->GetBT_MOVE()->GetButtonPress()) 
            {
                pathFinder->GetMap(GlobalMap->GetMap());
                pathFinder->FindPath(troop_manager->GetCurrentCharacter()->_pos, {savedPos.x - (cellW / 2) + (CurSize / 2), savedPos.y - (cellH / 2) + (CurSize / 2)});
                troop_manager->GetCurrentCharacter()->SetPoints(pathFinder->GetPath());

                for (auto i: troop_manager->GetCurrentCharacter()->GetPoints())
                {
                    std::cout << i;
                }
            
                pathFinder->ClearMap();
            }
        }
        
        else if (BT_ADDKNIGHT->GetButtonPress())
        {
            troop_manager->PushCharacter(new Character(CharacterType::WARRIOR,savedPos, 10));
        }
        else if (BT_ADDDEFENDER->GetButtonPress())
        {
           troop_manager->PushCharacter(new Character(CharacterType::DEFENDER,savedPos, 10));
        }
        else if (BT_ADDBUILDER->GetButtonPress())
        {
           troop_manager->PushCharacter(new Character(CharacterType::BUILDER,savedPos, 10));
        }

        if (troop_manager->GetCurrentCharacter())
        {
            troop_manager->UpdateButtons(GetMousePosition());
        }
        else
        {
            BT_ADDKNIGHT->Update(GetMousePosition());
            BT_ADDDEFENDER->Update(GetMousePosition());
            BT_ADDBUILDER->Update(GetMousePosition());
        }
        
        troop_manager->UpdateAllElements(deltaTime);

        BeginTextureMode(screen1);
        ClearBackground(blue);
        BeginMode2D(cam1);
        Draw();
        DrawRectangleLines(camPos.x, camPos.y, 200, 200, RED);
        DrawRectangle(savedPos.x, savedPos.y, CurSize, CurSize, PURPLE);
        EndMode2D();
        EndTextureMode();

        BeginTextureMode(screen2);
        ClearBackground(blue);
        BeginMode2D(cam2);
        Draw();
        EndMode2D();
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextureRec(screen1.texture, splitScreen, { 0,0 }, WHITE);
        DrawTextureRec(screen2.texture, splitScreen2, { 200,0 }, WHITE);

        if (troop_manager->GetCurrentCharacter())
        {
            troop_manager->DrawAllButtons();
        }
        else
        {
            BT_ADDKNIGHT->Draw();
            BT_ADDDEFENDER->Draw();
            BT_ADDBUILDER->Draw();
        }
        
        EndDrawing();
    }
    CloseWindow();
}

void Draw()
{
    DrawRectangle(0, 0, 10, 10, RED);
    DrawRectangle(180, 0, 10, 10, RED);
    DrawRectangle(0, 180, 10, 10, RED);
    GlobalMap->Draw(); 
    troop_manager->DrawAllElements(); 
}


int TurnToBaseX(int base, int num)
{
    int power = 0;
    while (num > base)
    {
        power++;
        num = num - base;
    }
    return (power * base);
}