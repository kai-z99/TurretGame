#include "Game.h"
#include <iostream>
#include <string>
#include "Turret.h"
#include "Enemy.h"
#include "SoldierEnemy.h"
#include "KoopaEnemy.h"
#include "RedKoopaEnemy.h"
#include "Bullet.h"
#include "TurretBullet.h"
#include "Hotbar.h"
#include "textures.h"
#include "helpers.h"
#include "VisualEffectsManager.h"

Game::Game()
{
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

    delete this->gameStats;
}

void Game::Run()
{

    
    while (!WindowShouldClose())
    {
        this->HandleEnemySpawning();
        this->HandleCollisions();
        this->HandleInput();
        this->Draw();
        this->Update();
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

    this->frameCount = 0;
    this->mousePos = { 0,0 };
    this->turret = new Turret();
    this->hotbar = new Hotbar();
    this->gameStats = new GameStats();
    this->effectManager = new VisualEffectsManager();
    this->gameStats->health = 100;
    this->gameStats->coins = 0;



}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    //draw bg
    DrawTexture(textures[6], 0, 0, WHITE);

    //draw boundaries
    DrawLine(deathBoundaryX, 0, deathBoundaryX, screenHeight, RED);
    DrawLine(0, menuBoundaryY, screenWidth, menuBoundaryY, RED);

    //draw turret
    this->turret->Draw();

    //draw enemies based on type. elsewise default enemy drawing behavoir.
    for (Enemy* e : enemies)
    {
        if (e->isActive) e->Draw();      
    }

    //draw bullets based on type. elsewise default enemy drawing behavoir.
    for (Bullet* b : bullets)
    {
        if (b->isActive)
        {
            b->Draw();
        }

    }

    //draw and update visual effects
    this->effectManager->UpdateAndDraw();

    //draw hotbar
    this->hotbar->Draw(this->gameStats);
    //draw mouse temp
    DrawCircle((int)this->mousePos.x, (int)this->mousePos.y, 5, BLUE);

    EndDrawing();
}

void Game::Update()
{
    //update frame
	this->frameCount++;

    //update mouse position
    mousePos = { GetMousePosition().x, GetMousePosition().y };

    this->hotbar->Update(this->frameCount);

    //update turret
    this->turret->Update(frameCount, (int)mousePos.x, (int)mousePos.y);

    //handle bullets
	for (Bullet* b : bullets)
	{
        if (b->isActive) b->Update(this->frameCount);
	}

    //handle enemies
	for (Enemy* e : enemies)
	{
        if (e->isActive)
        {
            e->Update(this->frameCount);

            //check if enemy has infiltrated the base
            if (e->GetPosition().x <= deathBoundaryX)
            {
                e->isActive = false;
                this->gameStats->health -= e->GetDamage();
            }
        }
		
	}

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
                if (e->isActive && b->EnemyCollided(e)) //if collide, remove buullet and deal damage
                {
                    //maybe make this a function?
                    this->effectManager->DisplayExplosion(b->GetPosition());
                   
                    //switch here maybe?
                    if (e->GetID() != 3)
                    {
                        e->SetHealth(e->GetHealth() - b->GetBaseDamage());
                        e->ApplyKnockback(b);
                    }

                   
                    // TEMP SOLUTION TO INVINCIBLE SHELL
                    //if its  red koopa only dmg when out of shell
                    else if (!dynamic_cast<RedKoopaEnemy*>(e)->shellForm)
                    {
                        e->SetHealth(e->GetHealth() - b->GetBaseDamage());
                        e->ApplyKnockback(b);
                    }

                    // if enemy died, add coin amount. and display coin effect
                    if (e->GetHealth() <= 0)
                    {
                        this->gameStats->coins += e->GetCoinDropAmount();
                        this->effectManager->DisplayCoinSplash(e->GetPosition(), e->GetCoinDropAmount());
                    }

                    b->isActive = false;
                }
                
            }
        }
        
        
    }
}

void Game::HandleInput()
{
    if (IsMouseButtonDown(0)) //check if turret shoot
    {
        //go through each bullet type
        for (const auto& cooldown : this->turret->GetBulletCooldownMap()) // bulletid : cooldownInfo
        {
            //if that type isnt on cooldown
            if (cooldown.second->canShoot)
            {
                //shoot that bullet type once.
                this->turret->ShootBullet(this->bullets, cooldown.first);
            }
        }

        if (bullets.size() > this->bulletLimit) this->CleanBulletVector(); //if the bullet vector is too big, cleanup
    
    }

    //check if each button isPressed. If it is, handle the event like rapidfire or something
}

void Game::CleanBulletVector() // keep all active bullet, delete rest from memory. Then clear bullet vector and add the remaing active ones to it.
{
    //std::cout << "old vector size" << this->bullets.size() << std::endl;
    std::vector<Bullet*> temp;

    for (Bullet* b : bullets) //keep active bullets, delete inative ones
    {
        if (b->isActive)
        {
            temp.push_back(b);
        }

        else delete b;
    }

    this->bullets.clear(); // clear the bullet vec

    this->bullets.insert(this->bullets.end(), temp.begin(), temp.end()); // copy the active bullets in temp back to empty bullet vector
    //std::cout << "new vector size" << this->bullets.size() << std::endl;
}


void Game::HandleEnemySpawning()
{
    if (this->frameCount % 300 == 0)
    {
        SoldierEnemy* s = new SoldierEnemy();
        s->SetPosition((float)screenWidth, (float)GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
        this->enemies.push_back(s);
    }

    if (this->frameCount % 500 == 0)
    {
        KoopaEnemy* k = new KoopaEnemy();
        k->SetPosition((float)screenWidth, (float)GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
        this->enemies.push_back(k);
    }

    if (this->frameCount % 400 == 0)
    {
        RedKoopaEnemy* k = new RedKoopaEnemy();
        k->SetPosition((float)screenWidth, (float)GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
        this->enemies.push_back(k);
    }

}

