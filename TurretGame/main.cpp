#include <iostream>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "constants.h"
#include "Turret.h"
#include "Projectile.h"
#include "helpers.h"


int main(void)
{
    InitWindow(screenWidth, screenHeight, "TurretGame window");
    SetTargetFPS(60);
    ToggleFullscreen();
    HideCursor();
    Turret t = Turret();
    Vector2 mousePos = { 0,0 };
    std::vector<Projectile*> projectiles;
    unsigned int frameCount = 0;

    while (!WindowShouldClose())
    {
        frameCount++;
        mousePos = { GetMousePosition().x, GetMousePosition().y };
        t.Update(frameCount, mousePos.x, mousePos.y);

        for (Projectile* p : projectiles)
        {
            p->Update();
        }

        if (IsMouseButtonDown(0) && t.GetCanShoot())
        {
            t.ShootProjectile(projectiles);
        }


        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawLine(deathBoundaryX, 0, deathBoundaryX, screenHeight, RED);
        t.Draw();

        for (Projectile* p : projectiles)
        {
            p->Draw();
        }

        
        if (IsMouseButtonDown(0)) DrawCircle(mousePos.x, mousePos.y, 5, BLUE);
        else DrawCircle(mousePos.x, mousePos.y, 5, RED);
        


        EndDrawing();
    }

    CloseWindow();

    return 0;
}

//game class
//create enemy
//different projectiles