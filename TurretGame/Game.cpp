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
#include "TurretLaser.h"
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
    //export new db
    DBFunctions::SaveDatabaseToFile("db.json"); //temp

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

void Game::SetGameStatsToDefault()
{
    //upgrade , {level,price,}
    this->gameStats->upgradeStates =
    {
        //should change to currentUpgradeInfo? no?
        {TurretBulletU,      UpgradeDatabase::INITIAL_UPGRADE_INFO.at(TurretBulletU)},
        {ShockwaveBulletU,   UpgradeDatabase::INITIAL_UPGRADE_INFO.at(ShockwaveBulletU)},
        {FireBulletU,        UpgradeDatabase::INITIAL_UPGRADE_INFO.at(FireBulletU)},
        {SniperBulletU,      UpgradeDatabase::INITIAL_UPGRADE_INFO.at(SniperBulletU)},
        {LightningBulletU,   UpgradeDatabase::INITIAL_UPGRADE_INFO.at(LightningBulletU)},
        {BombBulletU,        UpgradeDatabase::INITIAL_UPGRADE_INFO.at(BombBulletU)},
        {RapidfireU,         UpgradeDatabase::INITIAL_UPGRADE_INFO.at(RapidfireU)},
        {LaserU,             UpgradeDatabase::INITIAL_UPGRADE_INFO.at(LaserU)},
        {IceU,               UpgradeDatabase::INITIAL_UPGRADE_INFO.at(IceU)},
        {ExplosiveU,         UpgradeDatabase::INITIAL_UPGRADE_INFO.at(ExplosiveU)},
        {CloneU,             UpgradeDatabase::INITIAL_UPGRADE_INFO.at(CloneU)},
    };

    //get starting ability charges
    std::unordered_map<TurretAbility, short> startingCharges = DBFunctions::GetRoundStartAbilityCharges();

    this->gameStats->totalCoins = 0;
    this->gameStats->initialHealth = UpgradeDatabase::startingHealth;
}

//should be from db
void Game::SetAbilityStaticsToDefault()
{
    Turret::rapidFirerateMultiplier = 2.0f;
    Turret::rapidFireDuration = 240;

    TurretLaser::damage = 5.0f;
    TurretLaser::duration = 100;
    TurretLaser::color = RED;

    IceSheet::width = 500;
    IceSheet::height = 300;
    IceSheet::duration = 240;
    IceSheet::intensity = 5;

    BombExplosion::damage = 300.0f;
    BombExplosion::knockbackFrames = 30;
    BombExplosion::radius = 300.0f;
    BombExplosion::bulletRadius = 150.0f;

    Sentry::damageMultiplier = 0.5f;
    Sentry::duration = 500;
}

void Game::SetGameStatsToDatabaseValues()
{
    //merge db upgrade states to gamestats
    for (const auto& [upgrade,info] : UpgradeDatabase::currentUpgradeInfo)
    {
        this->gameStats->upgradeStates[upgrade] = info;
    }

    this->gameStats->totalCoins = UpgradeDatabase::totalCoins;
    this->gameStats->initialHealth = UpgradeDatabase::startingHealth;
    //now all we have to do is to use new upgrade info to set turret capabilities.
}

void Game::SetDatabaseValuesToGameStats()
{
    for (const auto& [upgrade, info] : this->gameStats->upgradeStates)
    {
        auto& [level, price] = info;

        UpgradeDatabase::currentUpgradeInfo[upgrade] = info;
    }
    
    UpgradeDatabase::totalCoins = this->gameStats->totalCoins;
    UpgradeDatabase::startingHealth = this->gameStats->initialHealth;
}

void Game::SetTurretsAndAbilitiesToUpgradeValues()
{
    //SET EVERYTHING TO DEFAULT AND SIMULATE UPGRADING IT [UPGRADELEVEL] TIMES.
    Turret* t = new Turret();

    Sentry* s1 = new Sentry();
    s1->SetPosition(100, 300);
    s1->SetTargetMode(1);

    Sentry* s2 = new Sentry();
    s2->SetPosition(100, 900);
    s2->SetTargetMode(0);
    

    this->SetAbilityStaticsToDefault();

    for (const auto& [upgrade, info] : this->gameStats->upgradeStates)
    {
        int level = info.first;
        int price = info.second;

        //loop upgradelevel amount of times to simulate upgrade that many times
        for (int i = 0; i < level; i++)
        {
            switch (upgrade)
            {
            case TurretBulletU:
                this->HandleBulletUpgrade(1, t, s1, s2);
                break;

            case ShockwaveBulletU: //id for shockwave bullet is 2
                this->HandleBulletUpgrade(2, t, s1, s2);
                break;

            case FireBulletU://id for shockwave bullet is 3
                this->HandleBulletUpgrade(3, t, s1, s2);
                break;

            case SniperBulletU:
                this->HandleBulletUpgrade(4, t, s1, s2);
                break;

            case LightningBulletU:
                this->HandleBulletUpgrade(5, t, s1, s2);
                break;

            case BombBulletU:
                this->HandleBulletUpgrade(6, t, s1, s2);
                break;

            case RapidfireU:
                this->HandleAbilityUpgrade(upgrade);
                break;

            case LaserU:
                this->HandleAbilityUpgrade(upgrade);
                break;

            case IceU:
                this->HandleAbilityUpgrade(upgrade);
                break;

            case ExplosiveU:
                this->HandleAbilityUpgrade(upgrade);
                break;

            case CloneU:
                this->HandleAbilityUpgrade(upgrade);
                break;

            default:
                std::cout << "Upgrade does not exist.";
                break;
            }
        }
    }

    delete this->turret;
    delete this->sentry1;
    delete this->sentry2;

    this->turret = t;
    this->sentry1 = s1;
    this->sentry2 = s2;
}

//helper
void Game::HandleBulletUpgrade(int bulletID, Turret* t, Sentry* s1, Sentry* s2)
{
    if (t->IsBulletUnlocked(bulletID)) t->SetFirerate(bulletID, t->GetFirerate(bulletID) + UpgradeDatabase::BULLET_FIRERATE_INCREASE_AMOUNTS.at(bulletID));
    else (t->UnlockBullet(bulletID));

    //sentries
    if (s1->IsBulletUnlocked(bulletID)) this->sentry1->SetFirerate(bulletID, this->sentry1->GetFirerate(bulletID) + 0.3f);
    else (s1->UnlockBullet(bulletID));

    if (s2->IsBulletUnlocked(bulletID)) this->sentry2->SetFirerate(bulletID, this->sentry2->GetFirerate(bulletID) + 0.3f);
    else (s2->UnlockBullet(bulletID));
}

//use db
void Game::HandleAbilityUpgrade(Upgrade upgrade)
{
    switch (upgrade)
    {
    case RapidfireU:
        Turret::rapidFirerateMultiplier += 0.12f;
        break;

    case LaserU:
        if (TurretLaser::duration >= 400)
        {
            TurretLaser::duration = 100;
            TurretLaser::damage += 15.0f;
            TurretLaser::color = RotateColorChannels(TurretLaser::color);
        }
            
        TurretLaser::duration += 100;
        break;

    case IceU:
        IceSheet::width += 20;
		IceSheet::height += 13;
		IceSheet::duration += 50;
		IceSheet::intensity += 20;
        break;

    case ExplosiveU:
        BombExplosion::radius += 10.0f;
		BombExplosion::damage += 170.0f;
		BombExplosion::knockbackFrames += 3;
        break;

    case CloneU:
        Sentry::damageMultiplier += 0.1f;
		Sentry::duration += 20;
        break;
    }
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

    this->SetGameStatsToDefault();
    DBFunctions::LoadDatabaseFromFile("db.json");
    this->SetGameStatsToDatabaseValues();

    //this->gameStats->upgradeStates = UpgradeDatabase::initialUpgradeInfo;

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
    this->hotbar = new Hotbar();
    this->SetTurretsAndAbilitiesToUpgradeValues();
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
        break;

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

