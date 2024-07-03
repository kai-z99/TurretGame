#include "LevelHandler.h"
#include <iostream>
#include "Game.h"
#include "LevelSpawner.h"

#include "types.h"
#include "constants.h"
#include "helpers.h"

#include "Bullet.h"
#include "Turret.h"
#include "TurretLaser.h"

#include "AreaEffect.h"
#include "IceSheet.h"
#include "BombExplosion.h"

#include "BatEnemy.h"
#include "SoldierEnemy.h"
#include "KoopaEnemy.h"
#include "RedKoopaEnemy.h"
#include "WolfEnemy.h"

#include "VisualEffectsManager.h"
#include "Hotbar.h"
#include "TryAgainButton.h"

#include "textures.h"


LevelHandler::LevelHandler(Game* game)
{
	this->game = game;
    this->levelSpawner = new LevelSpawner(this);
    this->enemiesRef = &game->enemies;
    this->currentLevelStats = new CurrentLevelStats();
    this->currentLevelFrameCount = 0;

    this->currentLevelComplete = false;
    this->currentLevelLose = false;

    this->cooldownWarningFrames = 0;
    this->chargeWarningFrames = 0;
}

void LevelHandler::Update(unsigned int frame)
{
    Game* g = this->game;

    this->currentLevelFrameCount++;

    //update hotbar buttons
    if (g->hotbar != nullptr) g->hotbar->Update(this->currentLevelFrameCount, this->currentLevelStats->abilityStates);

    //if an ability button is pressed, activate its ability if it has a charge.
    this->ActivateUsedAbilities();

    //update turret
    if (!this->currentLevelComplete && !this->currentLevelLose) g->turret->Update(g->frameCount, (int)g->mousePos.x, (int)g->mousePos.y);

    //handle bullets
    for (Bullet* b : g->bullets)
    {
        if (b->isActive) b->Update(g->frameCount);
    }

    for (AreaEffect* a : g->areaEffects)
    {
        if (a->isActive) a->Update(g->frameCount);
    }

    //handle enemies
    for (Enemy* e : g->enemies)
    {
        if (e->isActive)
        {
            e->Update(g->frameCount); //move enemy, apply effects, apply knockback. apply tint

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
            }
        }
    }   

    if (this->chargeWarningFrames > 0) this->chargeWarningFrames--;
    if (this->cooldownWarningFrames > 0) this->cooldownWarningFrames--;


    if (!this->currentLevelLose) this->HandleCurrentLevelSpawning();

    //handle try again
    else
    {
        g->tryAgainButton->Update(g->mousePos.x, g->mousePos.y);
    }

    

    //check win/loss
    if (this->currentLevelStats->health <= 0)
    {
        this->currentLevelLose = true;
    }

    else if (this->levelSpawner->IsFinishedSpawning() && this->NoActiveEnemies())
    {
        this->currentLevelComplete = true;
    }
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
        if (e->isActive) return false;
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

                default:
                    std::cout << a << "Ability does not exist.";
                    break;
                }
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
    //draw bg
    DrawTexture(textures[6], 0, 0, WHITE);

    //draw boundaries
    DrawLine(deathBoundaryX, 0, deathBoundaryX, screenHeight, RED);
    DrawLine(0, menuBoundaryY, screenWidth, menuBoundaryY, RED);

    //DRAW ICE UNDER
    for (AreaEffect* a : this->game->areaEffects)
    {
        //id 2 is ice
        if (a->isActive && a->GetID() == 2) a->Draw();
    }

    //draw enemies based on type. elsewise default enemy drawing behavoir.
    for (Enemy* e : this->game->enemies)
    {
        if (e->isActive) e->Draw();
    }

    //draw bullets based on type. elsewise default enemy drawing behavoir.
    for (Bullet* b : this->game->bullets)
    {
        if (b->isActive) b->Draw();
    }

    //draw turret
    this->game->turret->Draw();

    //DRAW EXPLOSION ON TOP
    for (AreaEffect* a : this->game->areaEffects)
    {
        //id 1 is bomb
        if (a->isActive && a->GetID() != 2) a->Draw();
    }

    //draw rolling effects
    this->DrawVisualEffects();

    //update and draw the effects that are on screen
    this->game->effectManager->UpdateAndDraw();

    //draw hotbar
    this->game->hotbar->Draw(*this->currentLevelStats);

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


    if (this->currentLevelComplete)
    {
        DrawText("LEVEL COMPLETE\n\n\nPress Enter to exit", 700, 700, 50, RED);
        this->cooldownWarningFrames = 0;
        this->chargeWarningFrames = 0;
    }

    else if (this->currentLevelLose)
    {
        DrawText("YOU DIED :(", screenWidth / 2, 400, 50, RED);
        this->game->tryAgainButton->Draw();
        this->cooldownWarningFrames = 0;
        this->chargeWarningFrames = 0;
    }
}

void LevelHandler::HandleInput()
{
    Game* g = this->game;

    if (this->currentLevelLose)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            this->currentLevelLose = false;
            this->DeInitializeCurrentLevel();
            this->InitializeCurrentLevel();
        }
        
    }

    else if (this->currentLevelComplete)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            this->currentLevelComplete = false;
            this->game->ExitCurrentLevel();
            this->game->gameState = LevelSelectMenu;
        }
        
        
    }

    else
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
                    g->areaEffects.push_back(new BombExplosion((int)g->mousePos.x, (int)g->mousePos.y));
                    break;
                    //ice
                case 2:
                    g->areaEffects.push_back(new IceSheet((int)g->mousePos.x, (int)g->mousePos.y));
                    break;
                }

                g->inputMode = 0;
            }
        }

        //standard shooting 
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

    this->game->gameStats->totalCoins += this->currentLevelStats->coinsCollected;

    this->currentLevelStats->coinsCollected = 0;
    this->currentLevelStats->health = 100;
    this->currentLevelFrameCount = 0;
    this->cooldownWarningFrames = 0;
    this->chargeWarningFrames = 0;
}


void LevelHandler::DrawVisualEffects()
{
    Game* g = this->game;
    //--------------
    //FIRE EFFECTS

    //draw burning enemies on fire
    for (Enemy* e : g->enemies)
    {
        if (e->isActive && e->GetStatusEffects()[Burning] % 8 == 7) g->effectManager->DisplayFire(e->GetPosition(), 1.0f);
    }

    
    for (Bullet* b : g->bullets)
    {
        //draw firebullet on fire
        if (b->isActive && b->GetID() == 3 && this->currentLevelFrameCount % 2 == 0)
        {
            Vector2 firePos = b->GetPosition();
            firePos.y -= 10;
            firePos.x -= 10;

            //make it look a bit more sparratic
            firePos.y += GetRandomValue(-5, 5);

            float scaleMod = GetRandomValue(-100, 100) * 0.0015f;

            g->effectManager->DisplayFire(firePos, 0.5f + scaleMod);
        }

        //sniperbullet trail
        else if (b->isActive && b->GetID() == 4 && this->currentLevelFrameCount % 2 == 0)
        {
            Vector2 firePos = b->GetPosition();

            //make it look a bit more sparratic
            firePos.y += GetRandomValue(-5, 5);

            float scaleMod = GetRandomValue(-100, 100) * 0.015f;

            g->effectManager->DisplayIceSparkle(firePos, 0.5f + scaleMod);
        }

    }

    //draw sparkles on ice sheet
    for (AreaEffect* a : g->areaEffects)
    {
        //id 2 is ice
        if (a->isActive && a->GetID() == 2)
        {
            Rectangle icebox = dynamic_cast<IceSheet*>(a)->GetHitbox();

            int offsetX = GetRandomValue((int)(-(icebox.width / 2)), (int)(icebox.width / 2));
            int offsetY = GetRandomValue((int)(-(icebox.height / 2)), (int)(icebox.height / 2));

            Vector2 pos = a->GetPosition();
            pos.x += offsetX;
            pos.y += offsetY;

            g->effectManager->DisplayIceSparkle(pos, GetRandomValue(-100, 100) * 0.02f);
        }
    }
}


