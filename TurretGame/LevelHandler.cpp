#include "LevelHandler.h"
#include <iostream>
#include "Game.h"

#include "types.h"
#include "constants.h"
#include "helpers.h"

#include "Bullet.h"
#include "AreaEffect.h"

#include "BatEnemy.h"
#include "SoldierEnemy.h"
#include "KoopaEnemy.h"
#include "RedKoopaEnemy.h"
#include "WolfEnemy.h"


LevelHandler::LevelHandler(Game* game)
{
	this->game = game;
    this->currentLevelStats = new CurrentLevelStats();
    this->currentLevelFrameCount = 0;
}

void LevelHandler::Update(unsigned int frame)
{
    this->currentLevelFrameCount++;
}

void LevelHandler::InitializeCurrentLevel()
{
    this->currentLevelFrameCount = 0;

    //set initial ability charges in this->currentLevelStats
    for (int i = 0; i <= 5; i++)
    {
        TurretAbility ability = static_cast<TurretAbility>(i);
        this->currentLevelStats->abilityStates[ability] = this->game->gameStats->initialAbilityValues[ability];
    }

    //set initial money and health
    this->currentLevelStats->coinsCollected = 0;
    this->currentLevelStats->health = 100;
}

void LevelHandler::ExitCurrentLevel()
{
    //display end screen here

    this->game->ClearVectors();
    this->game->gameStats->totalCoins += this->currentLevelStats->coinsCollected;

    this->currentLevelStats->coinsCollected = 0;
    this->currentLevelStats->health = 100;
    this->currentLevelFrameCount = 0;
}


void LevelHandler::HandleCurrentLevelSpawning()
{
    switch (this->game->currentLevel)
    {
    case 0:
        //menu
        break;

    //---------------------------------------------------------------------------------------------------//
    // LEVEL DIVIDER //----------------------------------------------------------------------------------//
    //---------------------------------------------------------------------------------------------------//

    case 1:
        if (this->currentLevelFrameCount % 30 == 0 && this->currentLevelFrameCount < 240)
        {
            BatEnemy* s = new BatEnemy();
            s->SetPosition((float)screenWidth, 500);
            s->SetAmplitude(3.0f);
            s->upStart = true;
            this->game->enemies.push_back(s);

        }
        break;

    //---------------------------------------------------------------------------------------------------//
    // LEVEL DIVIDER //----------------------------------------------------------------------------------//
    //---------------------------------------------------------------------------------------------------//

    case 2:
        if (this->currentLevelFrameCount % 30 == 0)
        {
            SoldierEnemy* s = new SoldierEnemy();
            s->SetPosition((float)screenWidth, (float)GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
            this->game->enemies.push_back(s);
        }

        if (this->currentLevelFrameCount % 500 == 0)
        {
            KoopaEnemy* k = new KoopaEnemy();
            k->SetPosition((float)screenWidth, (float)GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
            this->game->enemies.push_back(k);
        }

        if (this->currentLevelFrameCount % 400 == 0)
        {
            RedKoopaEnemy* k = new RedKoopaEnemy();
            k->SetPosition((float)screenWidth, (float)GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
            this->game->enemies.push_back(k);
        }

        if (this->currentLevelFrameCount % 410 == 0)
        {
            WolfEnemy* k = new WolfEnemy();
            k->SetPosition((float)screenWidth, (float)GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
            this->game->enemies.push_back(k);
        }

        if (this->currentLevelFrameCount % 300 == 0)
        {
            BatEnemy* s = new BatEnemy();
            s->SetPosition((float)screenWidth, (float)GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
            s->SetAmplitude(GetRandomFloat(1, 10));
            if (GetRandomValue(1, 2) == 1) s->upStart = true;
            this->game->enemies.push_back(s);
        }
        break;

    //---------------------------------------------------------------------------------------------------//
    // LEVEL DIVIDER //----------------------------------------------------------------------------------//
    //---------------------------------------------------------------------------------------------------//  

    default:
        std::cout << "WARNING: Level " << this->game->currentLevel << " does not exist.";
        break;
    }
}

void LevelHandler::SpawnClassicEnemy(int id)
{

}
