#include "LevelHandler.h"
#include <iostream>
#include "Game.h"
#include "LevelSpawner.h"

#include "types.h"
#include "constants.h"
#include "helpers.h"

#include "Bullet.h"
#include "Turret.h"
#include "Sentry.h"
#include "TurretLaser.h"

#include "AreaEffect.h"
#include "IceSheet.h"
#include "BombExplosion.h"

#include "BatEnemy.h"
#include "SoldierEnemy.h"
#include "KoopaEnemy.h"
#include "RedKoopaEnemy.h"
#include "WolfEnemy.h"
#include "SlimeEnemy.h"

#include "VisualEffectsManager.h"
#include "CollisionHandler.h"
#include "SoundHandler.h"
#include "Hotbar.h"
#include "TextButton.h"

#include "textures.h"


LevelHandler::LevelHandler(Game* game)
{
	this->game = game;
    this->levelSpawner = new LevelSpawner(this);
    this->enemiesRef = &game->enemies;
    this->currentLevelStats = new CurrentLevelStats();
    this->currentLevelFrameCount = 0;

    this->redScreen = { 255,0,0,0 };

    this->currentLevelComplete = false;
    this->currentLevelLose = false;

    this->cooldownWarningFrames = 0;
    this->chargeWarningFrames = 0;
    this->sentryFrames = 0;
}

void LevelHandler::Update(unsigned int frame)
{
    Game* g = this->game;

    this->currentLevelFrameCount++;

    if (this->redScreen.a > 0) this->redScreen.a -= 2;

    if (this->chargeWarningFrames > 0) this->chargeWarningFrames--;
    if (this->cooldownWarningFrames > 0) this->cooldownWarningFrames--;

    //fade lightning alpha. if fully faded, clear lightning points
    if (g->effectManager->lightningAlpha > 0) g->effectManager->lightningAlpha -= 10;
    if (g->effectManager->lightningAlpha <= 0) g->lightningPoints.clear();

    if (this->sentryFrames > 0) this->sentryFrames--;

    //update hotbar buttons
    if (g->hotbar != nullptr) g->hotbar->Update(this->currentLevelFrameCount, this->currentLevelStats->abilityStates);

    //if an ability button is pressed, activate its ability if it has a charge.
    this->ActivateUsedAbilities();

    //update turret and sentries
    if (!this->currentLevelComplete && !this->currentLevelLose)
    {
        g->turret->Update(g->frameCount, (int)g->mousePos.x, (int)g->mousePos.y);

        if (this->sentryFrames > 0)
        {
            g->sentry1->Update(g->frameCount, (int)g->mousePos.x, (int)g->mousePos.y, g->enemies, g->bullets);
            g->sentry2->Update(g->frameCount, (int)g->mousePos.x, (int)g->mousePos.y, g->enemies, g->bullets);
        }
        
    }
        
    //handle bullets
    for (Bullet* b : g->bullets)
    {
        if (b->isActive)
        {
            b->Update(g->frameCount);

            //CHECK FOR BULLET COLLISIONS
            for (Enemy* e : g->enemies)
            {
                if (e->isActive && b->EnemyCollided(e)) //if collide, remove buullet and deal damage
                {
                    g->collisionHandler->HandleBulletToEnemy(b, e);
                    g->soundHandler->HandleBulletCollisionSound(b);
                }
            }

            if (b->GetLocalFramecount() == 1)
            {
                g->soundHandler->HandleBulletShootSound(b);
            }
        }
    }

    for (AreaEffect* a : g->areaEffects)
    {
        if (a->isActive)
        {
            a->Update(g->frameCount);

            //CHECK IF ANY ENEMY COLLIDES WITH IT AND HANDLE EFFECT
            this->game->collisionHandler->HandleAOEToEnemies(a);       
        }      
    }

    //handle enemies
    for (Enemy* e : g->enemies)
    {
        if (e->isActive)
        {
            e->Update(g->frameCount); //move enemy, apply effects, apply knockback. apply tint

            //apply shock
            if (e->shocked)
            {
                e->SetHealth(e->GetHealth() - 50.0f);
                e->shocked = false;
            }

            // check if turret laser damages it
            if (g->turret->GetLaser()->isActive) this->game->collisionHandler->HandleLaserToEnemy(g->turret->GetLaser(), e);

            // if enemy died, add coin amount. and display coin effect
            if (e->GetHealth() <= 0)
            {
                this->currentLevelStats->coinsCollected += e->GetCoinDropAmount();
                g->effectManager->DisplayCoinSplash(e->GetPosition(), e->GetCoinDropAmount());
                e->isActive = false;
          
            }

            //check if enemy has infiltrated the base
            else if (e->GetPosition().x <= deathBoundaryX)
            {
                this->currentLevelStats->health -= e->GetDamage();
                if (this->currentLevelStats->health < 0) this->currentLevelStats->health = 0;
                e->isActive = false;

                //make screen red for a bit
                if (!this->currentLevelLose) this->redScreen.a = 60;
            }
        }
    }   

    //because bomb/ice mode freezes button update so these will keep appearing.
    if (g->inputMode != 0)
    {
        this->chargeWarningFrames = 0;
        this->cooldownWarningFrames = 0;
    }

    if (!this->currentLevelLose) this->HandleCurrentLevelSpawning();

    else
    {
        //handle try again button
        g->tryAgainButton->Update((int)g->mousePos.x, (int)g->mousePos.y);
    }
    
    //check win/loss
    if (this->currentLevelStats->health <= 0 && !this->currentLevelComplete)
    {
        this->currentLevelLose = true;
    }

    else if (this->levelSpawner->IsFinishedSpawning() && this->NoActiveEnemies())
    {
        this->currentLevelComplete = true;
        this->game->returnButton->Update((int)g->mousePos.x, (int)g->mousePos.y);
    }

    g->quitButton->Update((int)g->mousePos.x, (int)g->mousePos.y);
}

void LevelHandler::HandleCurrentLevelSpawning()
{
    this->levelSpawner->SetSpawnMap(this->game->currentLevel);
    this->levelSpawner->HandleCurrentLevelSpawning();
}

//helper
bool LevelHandler::NoActiveEnemies()
{
    for (Enemy* e : this->game->enemies)
    {
        if (e->isActive && e->GetID() != 8 && e->GetID() != 12 && e->GetID() != 13) return false; //id 8,12,13 are boss projectiles
    }

    return true;
}


//if an ability button is pressed, activate its ability if it has a charge and it is not on cooldown
void LevelHandler::ActivateUsedAbilities()
{
    Game* g = this->game;

    //go through every ablity that was clicked this frame
    for (const TurretAbility& a : g->hotbar->GetActiveAbilityButtons())
    {
        //info of the current ability
        AbilityInfo& info = this->currentLevelStats->abilityStates[a];

        //if the ablity has a chrage
        if (info.charges > 0)
        {
            // if the ability is ready,
            if (this->currentLevelFrameCount - info.lastUsedFrame >= (unsigned int)info.cooldown)
            {
                info.charges -= 1;
                info.lastUsedFrame = this->currentLevelFrameCount;

                switch (a)
                {
                case Rapidfire:
                    g->turret->SetRapidFire(240);
                    break;

                case Laser:
                    g->turret->SetLaserFrames(TurretLaser::duration);
                    break;

                case Explosive:
                    g->inputMode = 1; //1 is bomb place mode
                    break;

                case Ice:
                    g->inputMode = 2; //2 is ice mode
                    break;

                case Clone:
                    this->sentryFrames = Sentry::duration;
                    break;

                default:
                    std::cout << a << "Ability does not exist.";
                    break;
                }

                g->soundHandler->HandleActivateAbilitySound(a);
            }

            else
            {
                this->cooldownWarningFrames = 40;
            }
        }

        else
        {
            this->chargeWarningFrames = 40;
        }
    }

}

void LevelHandler::Draw()
{
    Game* g = this->game;
    //draw bg
   // DrawTexture(textures[6], 0, 0, WHITE);
    this->DrawCurrentLevelBackground();

    //draw boundaries
    DrawLine(deathBoundaryX, 0, deathBoundaryX, screenHeight, RED);
    DrawLine(0, menuBoundaryY, screenWidth, menuBoundaryY, RED);

    //DRAW ICE UNDER
    for (AreaEffect* a : g->areaEffects)
    {
        //id 2 is ice
        if (a->isActive && a->GetID() == 2) a->Draw();
    }

    //draw enemies based on type. elsewise default enemy drawing behavoir.
    for (Enemy* e : g->enemies)
    {
        if (e->isActive) e->Draw();
    }

    //draw bullets based on type. elsewise default enemy drawing behavoir.
    for (Bullet* b : g->bullets)
    {
        if (b->isActive) b->Draw();
    }

    //draw turret
    g->turret->Draw();

    //draw sentry
    if (this->sentryFrames > 0)
    {
        g->sentry1->Draw();
        g->sentry2->Draw();
    }
    

    //DRAW EXPLOSION ON TOP
    for (AreaEffect* a : g->areaEffects)
    {
        //id 1 is bomb
        if (a->isActive && a->GetID() != 2) a->Draw();
    }

    //update and draw the effects that are on screen
    g->effectManager->UpdateAndDraw();

    //draw redscreen 
    DrawRectangle(0,0,screenWidth,screenHeight,this->redScreen);


    //draw hotbar
    g->hotbar->Draw(*this->currentLevelStats, this->currentLevelFrameCount, this->levelSpawner->GetCurrentLevelLength());


    //draw warnings

    if (this->chargeWarningFrames > 0)
    {
        const char* text = "NO CHARGES AVAILIBLE";
        int width = MeasureText(text, 30);
        DrawText("NO CHARGES AVAILIBLE", (screenWidth / 2) - (width / 2), 300, 30, RED);
    }

    else if (this->cooldownWarningFrames > 0)
    {
        const char* text = "ABILITY ON COOLDOWN";
        int width = MeasureText(text, 30);
        DrawText("ABILITY ON COOLDOWN", (screenWidth / 2) - (width / 2), 300, 30, RED);
    }


    //draw win/lose screens

    if (this->currentLevelComplete)
    {
        this->game->returnButton->Draw();
        this->cooldownWarningFrames = 0;
        this->chargeWarningFrames = 0;
        this->game->inputMode = 0;
    }

    else if (this->currentLevelLose)
    {
        const char* text = "YOU DIED :(";
        int width = MeasureText(text, 50);

        DrawText(text, (screenWidth / 2) - (width / 2), 500, 50, RED);
        this->game->tryAgainButton->Draw();
        this->cooldownWarningFrames = 0;
        this->chargeWarningFrames = 0;
        this->game->inputMode = 0;
    }

    this->game->quitButton->Draw();
}

void LevelHandler::DrawCurrentLevelBackground()
{
    int lvl = this->game->currentLevel;
    Texture2D* bg;
    if (lvl > 0 && lvl < 6) bg = &textures[29];    // world 1
    else if (lvl == 6) bg = &textures[34]; //ballon boss
    else if (lvl >= 7 && lvl < 12) bg = &textures[37]; // world 2
    else if (lvl == 12) bg = &textures[35]; // wrld 2 boss
    else bg = &textures[3];

    Rectangle src = {0.0f, 0.0f, (float)bg->width, (float)bg->height};
    Rectangle dest = { screenWidth / 2.0f, screenHeight / 2.0f, (float)screenWidth, (float)screenHeight};
    Vector2 origin = { screenWidth / 2.0f, screenHeight / 2.0f };

    DrawTexturePro(*bg, src, dest, origin, 0.0f, WHITE);
}

void LevelHandler::HandleInput()
{
    Game* g = this->game;

    if (this->currentLevelLose)
    {
        if (g->tryAgainButton->isClicked)
        {
            this->currentLevelLose = false;
            g->tryAgainButton->isClicked = false; //since it doesnt update when its not active

            this->DeInitializeCurrentLevel();
            this->InitializeCurrentLevel();
        }

        else if (g->quitButton->isClicked)
        {
            this->currentLevelLose = false;
            g->quitButton->isClicked = false; //since it doesnt update when its not active

            g->ExitCurrentLevel();
            g->gameState = LevelSelectMenu;
            g->soundHandler->HandleGoToLevelSelect();
        }
        
    }

    else if (this->currentLevelComplete)
    {
        if (g->returnButton->isClicked || g->quitButton->isClicked)
        {
            this->currentLevelComplete = false;
            g->returnButton->isClicked = false;
            g->quitButton->isClicked = false;

            g->ExitCurrentLevel();
            g->gameState = LevelSelectMenu;
            g->soundHandler->HandleGoToLevelSelect();
        }  
    }

    else // in game
    {
        //bomb and ice place mode
        if (g->inputMode == 1 || g->inputMode == 2)
        {
            //if mouse is clicked in bounds
            if (IsMouseButtonPressed(0) && g->mousePos.y > menuBoundaryY)
            {
                switch (g->inputMode)
                {
                    //bomb
                case 1:
                    //push bomb in vector at x,y
                    g->areaEffects.push_back(new BombExplosion((int)g->mousePos.x, (int)g->mousePos.y, false));
                    break;
                    //ice
                case 2:
                    g->areaEffects.push_back(new IceSheet((int)g->mousePos.x, (int)g->mousePos.y));
                    break;
                }

                g->inputMode = 0;
            }
        }

        //standard shooting , quit availible
        else
        {
            //handle button clicking on hotbar (NOTE when in other input more this wont update so it will get stuck in a blue background after clikcing bomb or ice)
            g->hotbar->HandleInput();

            if (IsMouseButtonDown(0))
            {
                //go through each bullet type
                for (const auto& cooldown : g->turret->GetBulletCooldownMap()) // bulletid : cooldownInfo
                {
                    //if that type isnt on cooldown
                    if (cooldown.second->canShoot)
                    {
                        //shoot that bullet type once.
                        g->turret->ShootBullet(g->bullets, cooldown.first);
                    }
                }

                if (g->bullets.size() > g->bulletLimit) g->CleanBulletVector(); //if the bullet vector is too big, cleanup
            }

            if (g->quitButton->isClicked)
            {
                g->quitButton->isClicked = false;

                g->ExitCurrentLevel();
                g->gameState = LevelSelectMenu;
                g->soundHandler->HandleGoToLevelSelect();
            }
        }
    } 
}

void LevelHandler::InitializeCurrentLevel()
{
    this->currentLevelFrameCount = 0;
    this->cooldownWarningFrames = 0;
    this->chargeWarningFrames = 0;

    //set initial ability charges in this->currentLevelStats
    for (int i = 0; i <= 5; i++)
    {
        TurretAbility ability = static_cast<TurretAbility>(i);
        this->currentLevelStats->abilityStates[ability] = this->game->gameStats->initialAbilityValues[ability];
    }

    //set initial money and health
    this->currentLevelStats->coinsCollected = 0;
    this->currentLevelStats->health = this->game->gameStats->initialHealth;
}

void LevelHandler::DeInitializeCurrentLevel()
{
    //display end screen here
    this->game->ClearVectors();
    this->game->turret->SetLaserFrames(0);
    this->game->turret->SetRapidFire(0);
    this->sentryFrames = 0;
    this->game->inputMode = 0;

    this->game->gameStats->totalCoins += this->currentLevelStats->coinsCollected;

    this->currentLevelStats->coinsCollected = 0;
    this->currentLevelStats->health = 100;
    this->currentLevelFrameCount = 0;
    this->cooldownWarningFrames = 0;
    this->chargeWarningFrames = 0;
}


