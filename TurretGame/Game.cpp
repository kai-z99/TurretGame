#include "Game.h"
#include <iostream>
#include <string>

#include "types.h"
#include "helpers.h"

#include "LevelHandler.h"
#include "CollisionHandler.h"
#include "VisualEffectsManager.h"
#include "LevelSelectMenuHandler.h"
#include "UpgradeMenuHandler.h"

#include "Enemy.h"
#include "Bullet.h"
#include "Decoration.h"

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

    for (UpgradeButton* u : this->upgradeButtons)
    {
        delete u;
    }

    delete this->gameStats;

    if (this->hotbar != nullptr) delete this->hotbar;

    delete this->effectManager;

    delete this->collisionHandler;
    delete this->upgradeMenuHandler;
    delete this->levelSelectHandler;
    delete this->levelHandler;
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

void Game::DrawMousePos()
{
    std::string text = std::to_string(GetMouseX()) + "," + std::to_string(GetMouseY());
    DrawText(text.c_str(), this->mousePos.x, this->mousePos.y, 20.0f, BLACK);
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
    this->hotbar = nullptr;

    this->gameState = LevelSelectMenu;
    
    this->gameStats = new GameStats();
    this->effectManager = new VisualEffectsManager();
   
    this->gameStats->totalCoins = 10000;
    this->gameStats->initialHealth = 100;

    this->currentLevel = 1;

    this->inputMode = false;

    
    //temp
    this->gameStats->initialAbilityValues =
    {
        // type, {cooldown, lastshotframe, maxcharges, charges}
        {Rapidfire, {550, INT_MIN, 1, 1}},
        {Laser, {700, INT_MIN, 0, 0}},
        {Explosive, {800, INT_MIN, 0, 0}},
        {Ice, {750, INT_MIN, 0, 0}},
        {Shock, {550, INT_MIN, 0, 0}},
        {Burn, {550, INT_MIN, 0, 0}}
    };

    //upgrade , {level,price,}
    this->gameStats->upgradeStates =
    {
        {TurretBulletU,{1, 50}},
        {ShockwaveBulletU,{0, 150}},
        {FireBulletU,{0, 150}},
        {SniperBulletU,{0, 150}},
        {RapidfireU,{1, 150}},
        {LaserU,{0, 150}},
        {IceU,{0, 150}},
        {ExplosiveU, {0, 150}},
    };

    this->levelHandler = new LevelHandler(this);
    this->collisionHandler = new CollisionHandler(this);
    this->levelSelectHandler = new LevelSelectHandler(this);
    this->upgradeMenuHandler = new UpgradeMenuHandler(this);

    //this->hotbar = new Hotbar(this->levelHandler->currentLevelStats->abilityStates); 
    
}

//-------------------------------------------------------------------------------------

void Game::StartCurrentLevel()
{
    this->levelHandler->InitializeCurrentLevel();
    this->hotbar = new Hotbar(this->levelHandler->currentLevelStats->abilityStates);
    //this->turret = new Turret();
}

void Game::ExitCurrentLevel()
{
    this->levelHandler->DeInitializeCurrentLevel();

    delete this->hotbar;
    this->hotbar = nullptr;

    //delete this->turret;
    //this->turret = nullptr;
}

//------------------------------------------------------------------------------------

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

    case UpgradeMenu:
        this->DrawUpgradeMenu();
        break;
    }

    //make this a function
    //draw mouse
    if (!this->inputMode) DrawCircle((int)this->mousePos.x, (int)this->mousePos.y, 5.0f, GREEN);

    //draw mouse in place mode
    else
    {
        DrawCircleLines((int)this->mousePos.x, (int)this->mousePos.y, 35.0f, RED);
        DrawLineEx({ this->mousePos.x - 30, this->mousePos.y - 30 }, { this->mousePos.x + 30, this->mousePos.y + 30 }, 1.0f, RED);
        DrawLineEx({ this->mousePos.x + 30, this->mousePos.y - 30 }, { this->mousePos.x - 30, this->mousePos.y + 30 }, 1.0f, RED);
    }
    this->DrawMousePos();
    EndDrawing();
}

void Game::DrawInLevel()
{
    this->levelHandler->Draw();
}

void Game::DrawLevelSelectMenu()
{
    ClearBackground(RAYWHITE); // temp

    this->levelSelectHandler->Draw();

}

void Game::DrawUpgradeMenu()
{
    ClearBackground(DARKGREEN);
   
    this->upgradeMenuHandler->Draw();
}

//------------------------------------------------------------------------------------

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

    case UpgradeMenu:
        this->UpdateUpgradeMenu();
    }
}

void Game::UpdateInLevel()
{
    this->levelHandler->Update(this->frameCount);
    this->collisionHandler->HandleEnemyCollisions();
}

void Game::UpdateLevelSelectMenu()
{
    this->levelSelectHandler->Update(this->frameCount);
}

void Game::UpdateUpgradeMenu()
{
    this->upgradeMenuHandler->Update();
}

//------------------------------------------------------------------------------------

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
        this->HandleInputUpgradeMenu();
        break;

    default:
        break;
    }
    
    
}

void Game::HandleInputInLevel()
{
    this->levelHandler->HandleInput();
    
    //debug
    if (IsKeyPressed(KEY_UP))
    {
        this->ExitCurrentLevel();
        this->gameState = LevelSelectMenu;
    }
}

void Game::HandleInputLevelSelectMenu()
{
    this->levelSelectHandler->HandleInput();

    if (IsKeyPressed(KEY_UP))
    {
        this->gameState = UpgradeMenu;
    }
}

void Game::HandleInputUpgradeMenu()
{
    this->upgradeMenuHandler->HandleInput();
}

//------------------------------------------------------------------------------

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

