#include "Game.h"
#include <iostream>
#include <string>

#include "types.h"
#include "helpers.h"

#include "LevelHandler.h"
#include "CollisionHandler.h"
#include "VisualEffectsManager.h"

#include "Enemy.h"
#include "Bullet.h"

#include "BombExplosion.h"
#include "IceSheet.h"
#include "Turret.h"
#include "Hotbar.h"

#include "textures.h"

Game::Game()
{
    this->Initialize();
}

Game::~Game()
{
    //this should be unload level
	for (Bullet* b : this->bullets)
	{
		delete b;
	}

	for (Enemy* e : this->enemies)
	{
		delete e;
	}

    for (AreaEffect* a : this->areaEffects)
    {
        delete a;
    }

    delete this->gameStats;

    delete this->hotbar;

    delete this->effectManager;
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        this->HandleInput();
        this->Update();
        this->Draw();
    }

    CloseWindow();
}

void Game::ClearVectors()
{
    for (Enemy* e : this->enemies)
    {
        delete e;
    }

    this->enemies.clear();

    for (Bullet* b : this->bullets)
    {
        delete b;
    }

    this->bullets.clear();

    for (AreaEffect* a : this->areaEffects)
    {
        delete a;
    }

    this->areaEffects.clear();

    //cleans task vector
    this->effectManager->Clear();
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

    this->turret = nullptr;
    this->hotbar = nullptr;

    this->gameState = InLevel;
    
    this->gameStats = new GameStats();
    this->effectManager = new VisualEffectsManager();

    this->gameStats->totalCoins = 0;
    
    this->currentLevel = 1;

    this->inputMode = false;

    
    //temp
    this->gameStats->initialAbilityValues =
    {
        // type, {cooldown, lastshotframe, maxcharges, charges}
        {Rapidfire, {550, INT_MIN, 5, 5}},
        {SpecialRapidfire, {700, INT_MIN, 3, 3}},
        {Explosive, {800, INT_MIN, 2, 2}},
        {Ice, {750, INT_MIN, 5, 5}},
        {Shock, {550, INT_MIN, 5, 5}},
        {Burn, {550, INT_MIN, 5, 5}}
    };

    this->levelHandler = new LevelHandler(this);
    this->collisionHandler = new CollisionHandler(this);

    this->StartCurrentLevel();

    //this->hotbar = new Hotbar(this->levelHandler->currentLevelStats->abilityStates); 
    
}

void Game::StartCurrentLevel()
{
    this->levelHandler->InitializeCurrentLevel();
    this->hotbar = new Hotbar(this->levelHandler->currentLevelStats->abilityStates);
    this->turret = new Turret();
}

void Game::ExitCurrentLevel()
{
    this->levelHandler->ExitCurrentLevel();

    delete this->hotbar;
    this->hotbar = nullptr;

    delete this->turret;
    this->turret = nullptr;
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    switch (this->gameState)
    {
    case InLevel:
        this->DrawInLevel();
        break;

    case LevelSelectMenu:
        this->DrawLevelSelectMenu();
        break;

    }

    //draw mouse
    if (!this->inputMode) DrawCircle((int)this->mousePos.x, (int)this->mousePos.y, 5.0f, BLUE);

    //draw mouse in place mode
    else
    {
        DrawCircleLines((int)this->mousePos.x, (int)this->mousePos.y, 35.0f, RED);
        DrawLineEx({ this->mousePos.x - 30, this->mousePos.y - 30 }, { this->mousePos.x + 30, this->mousePos.y + 30 }, 1.0f, RED);
        DrawLineEx({ this->mousePos.x + 30, this->mousePos.y - 30 }, { this->mousePos.x - 30, this->mousePos.y + 30 }, 1.0f, RED);
    }

    EndDrawing();
}

void Game::DrawInLevel()
{
    this->levelHandler->Draw();
}

void Game::DrawLevelSelectMenu()
{

    ClearBackground(RAYWHITE); // temp

    DrawTexture(textures[1], 500, 500, WHITE);
    DrawTexture(textures[1], 800, 500, WHITE);
    DrawTexture(textures[1], 500, 1000, WHITE);
    DrawTexture(textures[1], 500, 200, WHITE);
    DrawTexture(textures[1], 100, 800, WHITE);

}

void Game::Update()
{
    //update frame
	this->frameCount++;

    //update mouse position
    mousePos = { GetMousePosition().x, GetMousePosition().y };

    switch (this->gameState)
    {
    case InLevel:
        this->UpdateInLevel();
        break;

    case LevelSelectMenu:
        this->UpdateLevelSelectMenu();
        break;
    }
}

void Game::UpdateInLevel()
{
    this->levelHandler->Update(this->frameCount);
    this->levelHandler->HandleCurrentLevelSpawning(); //part of update??:
    this->collisionHandler->HandleEnemyCollisions();
}

void Game::UpdateLevelSelectMenu()
{

}




void Game::HandleInput()
{
    switch (this->gameState)
    {
    case InLevel:
        this->HandleInputInLevel();
        break;

    case LevelSelectMenu:
        this->HandleInputLevelSelectMenu();
        break;

    case MainMenu:
        break;

    case UpgradeMenu:
        break;

    default:
        break;
    }
    
    //debug
    if (IsKeyPressed(KEY_RIGHT))
    {
        this->ExitCurrentLevel();
        this->currentLevel++;
        this->StartCurrentLevel();
    }
    else if (IsKeyPressed(KEY_LEFT))
    {
        this->ExitCurrentLevel();
        this->currentLevel--;
        this->StartCurrentLevel();
    }
    else if (IsKeyPressed(KEY_UP))
    {
        this->ExitCurrentLevel();
        this->gameState = LevelSelectMenu;
    }
}

void Game::HandleInputInLevel()
{
    //bomb and ice place mode
    if (this->inputMode == 1 || this->inputMode == 2)
    {
        //if mouse is clicked in bounds
        if (IsMouseButtonPressed(0) && this->mousePos.y > menuBoundaryY)
        {
            switch (this->inputMode)
            {
                //bomb
            case 1:
                //push bomb in vector at x,y
                this->areaEffects.push_back(new BombExplosion((int)this->mousePos.x, (int)this->mousePos.y));
                break;
                //ice
            case 2:
                this->areaEffects.push_back(new IceSheet((int)this->mousePos.x, (int)this->mousePos.y, 350));
                break;
            }

            this->inputMode = 0;
        }
    }

    //standard shooting 
    else
    {
        //handle button clicking on hotbar (NOTE when in other input more this wont update so it will get stuck in a blue background after clikcing bomb or ice)
        this->hotbar->HandleInput();

        if (IsMouseButtonDown(0))
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
    }


}

void Game::HandleInputLevelSelectMenu()
{

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

