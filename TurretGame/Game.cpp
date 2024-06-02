#include "Game.h"
#include <iostream>
#include <string>
#include "Turret.h"
#include "Enemy.h"
#include "SoldierEnemy.h"
#include "KoopaEnemy.h"
#include "Bullet.h"
#include "TurretBullet.h"
#include "textures.h"


Game::Game()
{
    this->frameCount = 0;
    this->mousePos = { 0,0 };
    this->Initialize();
}

Game::~Game()
{
	for (Bullet* b : this->bullets)
	{
		delete b;
	}

	for (Enemy* e : this->enemies)
	{
		delete e;
	}
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        this->Update();
        this->HandleEnemySpawning();
        this->HandleCollisions();
        this->HandleInput();
        this->Draw();
    }

    CloseWindow();
}

void Game::Initialize()
{
    InitWindow(screenWidth, screenHeight, "TurretGame window");
    SetTargetFPS(60);
    //ToggleFullscreen();
    HideCursor();

    LoadAllTextures(); // ONLY WORKS AFTER INITIWINDOW

    this->playerHealth = 100;
    this->turret = new Turret();
   // this->turret->SetFirerate(15.0f);
    //temp
    SoldierEnemy* s = new SoldierEnemy();
    s->SetPosition(screenWidth, screenHeight / 2);

    this->enemies.push_back(s);
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    //draw boundaries
    DrawLine(deathBoundaryX, 0, deathBoundaryX, screenHeight, RED);
    DrawLine(0, menuBoundaryY, screenWidth, menuBoundaryY, RED);

    //draw mouse temp
    DrawCircle(this->mousePos.x, this->mousePos.y, 5, BLUE);

    //draw health
    DrawText(std::to_string(this->playerHealth).c_str(), 30, 30, 40, RED);

    //draw turret
    this->turret->Draw();

    //draw enemies based on type. elsewise default enemy drawing behavoir.
    for (Enemy* e : enemies)
    {
        if (e->isActive)
        {
            switch (e->GetID())
            {
            case 1:
                dynamic_cast<SoldierEnemy*>(e)->Draw();
                break;

            default:
                std::cout << "Unkown enemy type: using default draw.\n";
                e->Draw();
                break;
            }
        }
            
    }

    //draw bullets based on type. elsewise default enemy drawing behavoir.
    for (Bullet* b : bullets)
    {
        if (b->isActive)
        {
            switch (b->GetID())
            {
            case 1:
                dynamic_cast<TurretBullet*>(b)->Draw();
                break;

            default:
                std::cout << "Unkown bullet type: using default draw.\n";
                b->Draw();
                break;
            }
        }

    }

    EndDrawing();
}

void Game::Update()
{
    //update frame
	this->frameCount++;

    //update mouse position
    mousePos = { GetMousePosition().x, GetMousePosition().y };


    //update turret
    this->turret->Update(frameCount, mousePos.x, mousePos.y);

    //handle bullets
	for (Bullet* b : bullets)
	{
        if (b->isActive)
        {
            switch (b->GetID())
            {
            case 1:
                dynamic_cast<TurretBullet*>(b)->Update();
                break;

            default:
                std::cout << "Unkown bullet type: using default update.\n";
                b->Update();
                break;
            }
        }
		
	}

    //handle enemies
	for (Enemy* e : enemies)
	{
        if (e->isActive)
        {
            switch (e->GetID())
            {
            case 1:
                dynamic_cast<SoldierEnemy*>(e)->Update(this->frameCount);
                break;

            default:
                std::cout << "Unkown enemy type: using default update.\n";
                e->Update(this->frameCount);
                break;
            }

            if (e->GetPosition().x <= deathBoundaryX)
            {
                e->isActive = false;
                this->playerHealth -= e->GetDamage();
            }
        }
		
	}

    //enemy spawning
}

//check if bullets hits enemys
void Game::HandleCollisions()
{
    for (Bullet* b : bullets)
    {
        if (b->isActive)
        {
            for (Enemy* e : enemies)
            {
                if (e->isActive && b->EnemyCollided(e))
                {
                    b->isActive = false;
                    e->SetHealth(e->GetHealth() - b->GetBaseDamage());
                }
                
            }
        }
        
        
    }
}

void Game::HandleInput()
{
    if (IsMouseButtonDown(0) && this->turret->GetCanShoot())
    {
        if (bullets.size() > this->bulletLimit) this->CleanBulletVector();

        this->turret->ShootProjectile(bullets);
        
    }
}

void Game::CleanBulletVector()
{
    //std::cout << "old vector size" << this->bullets.size() << std::endl;
    std::vector<Bullet*> temp;

    for (Bullet* b : bullets)
    {
        if (b->isActive)
        {
            temp.push_back(b);
        }

        else delete b;
    }

    this->bullets.clear();

    this->bullets.insert(this->bullets.end(), temp.begin(), temp.end()); // copy bullets in temp to empty bullet vector
    //std::cout << "new vector size" << this->bullets.size() << std::endl;
}


void Game::HandleEnemySpawning()
{
    if (this->frameCount % 60 == 0)
    {
        SoldierEnemy* s = new SoldierEnemy();
        s->SetPosition(screenWidth, GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
        this->enemies.push_back(s);
    }

    if (this->frameCount % 77 == 0)
    {
        KoopaEnemy* k = new KoopaEnemy();
        k->SetPosition(screenWidth, GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
        this->enemies.push_back(k);
    }
}

