#include "Game.h"
#include <iostream>
#include <string>

#include "types.h"
#include "helpers.h"
#include "Database.h"

#include "LevelHandler.h"
#include "CollisionHandler.h"
#include "VisualEffectsManager.h"
#include "LevelSelectMenuHandler.h"
#include "UpgradeMenuHandler.h"
#include "MainMenuHandler.h"
#include "SoundHandler.h"

#include "Enemy.h"
#include "Bullet.h"
#include "Decoration.h"
#include "TextButton.h"
#include "UpgradeButton.h"

#include "BombExplosion.h"
#include "IceSheet.h"
#include "Turret.h"
#include "Sentry.h"
#include "Hotbar.h"

#include "textures.h"
#include "sounds.h"

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

    delete this->tryAgainButton;
    delete this->returnButton;
    delete this->quitButton;
    delete this->shopButton;

    UnloadAllTextures();
    UnloadAllSounds();
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
    DrawText(text.c_str(), (int)this->mousePos.x, (int)this->mousePos.y, 20, BLACK);
}

void Game::Initialize()
{
    InitWindow(screenWidth, screenHeight, "TurretGame window");
    SetTargetFPS(60);  
    //ToggleFullscreen();
    //ToggleBorderlessWindowed();
    HideCursor();
    LoadAllTextures(); // ONLY WORKS AFTER INITIWINDOW
    LoadAllSounds();

    this->frameCount = 0;
    this->mousePos = { 0,0 };

    this->turret = new Turret();
    this->hotbar = nullptr;

    this->gameState = MainMenu;
    
    this->gameStats = new GameStats();
    this->effectManager = new VisualEffectsManager(this);

    //BUTTONS------------------------------------------

    int width = 500;
    int height = 200;
    int posX = (screenWidth / 2) - (width / 2);
    int posY = (screenHeight / 2) - (height / 2) + 200;

    this->tryAgainButton = new TextButton(posX, posY, width, height, "TRY AGAIN");
    this->returnButton = new TextButton(posX, posY, width, height, "RETURN TO MENU");

    width = 130;
    height = 130;
    posX = screenWidth - width - 10;
    posY = (menuBoundaryY / 2) - (height / 2);

    this->quitButton = new TextButton(posX, posY, width, height, "QUIT");

    width = 230;
    height = 130;
    posX = 10;
    posY = (menuBoundaryY / 2) - (height / 2);

    this->shopButton = new TextButton(posX, posY, width, height, "SHOP");
    
    width = 230;
    height = 130;
    posX = (screenWidth / 2) - (width / 2);
    posY = 700;

    this->startButton = new TextButton(posX, posY, width, height, "START!");


    //------------------------------------------------


    this->gameStats->totalCoins = 50000;
    this->gameStats->initialHealth = 30;

    this->currentLevel = 1;

    this->inputMode = false;

    this->sentry1 = new Sentry();
    this->sentry1->SetPosition(100, 300);
    this->sentry1->SetTargetMode(1);

    this->sentry2 = new Sentry();
    this->sentry2->SetPosition(100, 900);
    this->sentry2->SetTargetMode(0);
    
    //temp
    //this->gameStats->initialAbilityValues =
    //{
    //    // type, {cooldown, lastshotframe, maxcharges, charges}
    //    {Rapidfire, {550, INT_MIN, 1, 1}},
    //    {Laser, {700, INT_MIN, 0, 0}},
    //    {Explosive, {800, INT_MIN, 0, 0}},
    //    {Ice, {750, INT_MIN, 0, 0}},
    //    {Clone, {1000, INT_MIN, 0, 0}},
    //};

    //get starting ability charges
    std::unordered_map<TurretAbility, short> startingCharges = AbilityDatabase::GetRoundStartAbilityCharges();

    this->gameStats->initialAbilityValues =
    {
        // type,    {               cooldown,                       lastshotframe,     maxcharges,                    charges}
        {Rapidfire, {AbilityDatabase::abilityCooldowns.at(Rapidfire), INT_MIN, startingCharges[Rapidfire], startingCharges[Rapidfire]}},
        {Laser,     {AbilityDatabase::abilityCooldowns.at(Laser),     INT_MIN, startingCharges[Laser],     startingCharges[Laser]}},
        {Explosive, {AbilityDatabase::abilityCooldowns.at(Explosive), INT_MIN, startingCharges[Explosive], startingCharges[Explosive]}},
        {Ice,       {AbilityDatabase::abilityCooldowns.at(Ice),       INT_MIN, startingCharges[Ice],       startingCharges[Ice]}},
        {Clone,     {AbilityDatabase::abilityCooldowns.at(Clone),     INT_MIN, startingCharges[Clone],     startingCharges[Clone]}},
    };

    //upgrade , {level,price,}
    this->gameStats->upgradeStates =
    {
        {TurretBulletU,      UpgradeDatabase::initalUpgradeInfo.at(TurretBulletU)},
        {ShockwaveBulletU,   UpgradeDatabase::initalUpgradeInfo.at(ShockwaveBulletU)},
        {FireBulletU,        UpgradeDatabase::initalUpgradeInfo.at(FireBulletU)},
        {SniperBulletU,      UpgradeDatabase::initalUpgradeInfo.at(SniperBulletU)},
        {LightningBulletU,   UpgradeDatabase::initalUpgradeInfo.at(LightningBulletU)},
        {BombBulletU,        UpgradeDatabase::initalUpgradeInfo.at(BombBulletU)},
        {RapidfireU,         UpgradeDatabase::initalUpgradeInfo.at(RapidfireU)},
        {LaserU,             UpgradeDatabase::initalUpgradeInfo.at(LaserU)},
        {IceU,               UpgradeDatabase::initalUpgradeInfo.at(IceU)},
        {ExplosiveU,         UpgradeDatabase::initalUpgradeInfo.at(ExplosiveU)},
        {CloneU,             UpgradeDatabase::initalUpgradeInfo.at(CloneU)},
    };

    this->gameStats->upgradeStates = UpgradeDatabase::initalUpgradeInfo;

    this->levelHandler = new LevelHandler(this);
    this->collisionHandler = new CollisionHandler(this);
    this->levelSelectHandler = new LevelSelectHandler(this);
    this->upgradeMenuHandler = new UpgradeMenuHandler(this);
    this->mainMenuHandler = new MainMenuHandler(this);
    this->soundHandler = new SoundHandler(this);
    this->soundHandler->HandleGoToMainMenu();

    //this->hotbar = new Hotbar(this->levelHandler->currentLevelStats->abilityStates); 
    this->lightningPoints = {};
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

    this->lightningPoints.clear();

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

    case MainMenu:
        this->DrawMainMenu();
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

    //DrawFPS(0, 0);

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

void Game::DrawMainMenu()
{
    this->mainMenuHandler->Draw();
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

    case MainMenu:
        this->UpdateMainMenu();
        break;
    }

    this->soundHandler->Update();
}

void Game::UpdateInLevel()
{
    this->levelHandler->Update(this->frameCount);
}

void Game::UpdateLevelSelectMenu()
{
    this->levelSelectHandler->Update(this->frameCount);
}

void Game::UpdateUpgradeMenu()
{
    this->upgradeMenuHandler->Update();
}

void Game::UpdateMainMenu()
{
    this->mainMenuHandler->Update(this->frameCount);
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

    case UpgradeMenu:
        this->HandleInputUpgradeMenu();
        break;

    case MainMenu:
        this->HandleInputMainMenu();
        break;

    default:
        break;
    }
   
}

void Game::HandleInputInLevel()
{
    this->levelHandler->HandleInput();
}

void Game::HandleInputLevelSelectMenu()
{
    this->levelSelectHandler->HandleInput();
}

void Game::HandleInputUpgradeMenu()
{
    this->upgradeMenuHandler->HandleInput();
}

void Game::HandleInputMainMenu()
{
    this->mainMenuHandler->HandleInput();
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

