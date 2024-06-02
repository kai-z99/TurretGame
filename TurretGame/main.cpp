#include <iostream>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "constants.h"
#include "Turret.h"
#include "Projectile.h"
#include "Bullet.h"
#include "SoldierEnemy.h"
#include "helpers.h"


int main(void)
{
    InitWindow(screenWidth, screenHeight, "TurretGame window");
    SetTargetFPS(60);
    //ToggleFullscreen();
    HideCursor();
    Turret t = Turret();

    SoldierEnemy* s = new SoldierEnemy();
    s->SetPosition(screenWidth - 100, screenHeight / 2);


    Vector2 mousePos = { 0,0 };
    std::vector<Bullet*> bullets;
    unsigned int frameCount = 0;

    while (!WindowShouldClose())
    {
        frameCount++;
        mousePos = { GetMousePosition().x, GetMousePosition().y };
        t.Update(frameCount, mousePos.x, mousePos.y);

        if (s->IsActive()) s->Update(frameCount);
        
        for (Bullet* p : bullets)
        {
            if (p->isActive)
            {
                p->Update();

                if (p->EnemyCollided(s))
                {
                    p->isActive = false;
                    s->SetHealth(s->GetHealth() - 1);
                }
            }
       
        }

        if (IsMouseButtonDown(0) && t.GetCanShoot())
        {
            t.ShootProjectile(bullets);
        }

        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawLine(deathBoundaryX, 0, deathBoundaryX, screenHeight, RED);
        DrawLine(0, menuBoundaryY, screenWidth, menuBoundaryY, RED);
        t.Draw();

        if (s->IsActive()) s->Draw();

        
        for (Bullet* p : bullets)
        {
            if (p->isActive) p->Draw();
            
        }

        
        if (IsMouseButtonDown(0)) DrawCircle(mousePos.x, mousePos.y, 5, BLUE);
        else DrawCircle(mousePos.x, mousePos.y, 5, RED);
        


        EndDrawing();
    }

    CloseWindow();

    return 0;
}

//bg image
//game class
//create enemy
//different projectiles