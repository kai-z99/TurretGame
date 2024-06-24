#include "LevelHandler.h"
#include <iostream>
#include "Game.h"
#include "LevelBuilder.h"

#include "types.h"
#include "constants.h"
#include "helpers.h"

#include "Bullet.h"
#include "Turret.h"

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

#include "textures.h"


LevelHandler::LevelHandler(Game* game)
{
	this->game = game;
    this->levelBuilder = new LevelBuilder(this);
    this->enemiesRef = &game->enemies;
    this->currentLevelStats = new CurrentLevelStats();
    this->currentLevelFrameCount = 0;
}

void LevelHandler::Update(unsigned int frame)
{
    Game* g = this->game;

    this->currentLevelFrameCount++;

    //update hotbar buttons
    if (g->hotbar != nullptr) g->hotbar->Update(g->frameCount, this->currentLevelStats->abilityStates);

    //if an ability button is pressed, activate its ability if it has a charge.
    this->ActivateUsedAbilities();

    //update turret
    g->turret->Update(g->frameCount, (int)g->mousePos.x, (int)g->mousePos.y);

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
                e->isActive = false;
            }
        }
    }   
}

void LevelHandler::ActivateUsedAbilities()
{
    Game* g = this->game;

    //if an ability button is pressed, activate its ability if it has a charge and it is not on cooldown

    //go through every ablity that was clicked this frame
    for (const TurretAbility& a : g->hotbar->GetActiveAbilityButtons())
    {
        //info of the current ability
        AbilityInfo& info = this->currentLevelStats->abilityStates[a];

        // if the ability is ready,
        if (g->frameCount - info.lastUsedFrame >= (unsigned int)info.cooldown)
        {
            //if there is an availible chrage, use one.
            if (info.charges > 0)
            {
                info.charges -= 1;
                info.lastUsedFrame = g->frameCount;

                switch (a)
                {
                case Rapidfire:
                    g->turret->SetRapidFire(240);
                    break;

                case SpecialRapidfire:
                    g->turret->SetSpecialRapidfire(240);
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
                // no charges splash
            }

        }

        else
        {
            //ability is not ready splash
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

    //draw turret
    this->game->turret->Draw();

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
}

void LevelHandler::HandleInput()
{
    Game* g = this->game;

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
                g->areaEffects.push_back(new IceSheet((int)g->mousePos.x, (int)g->mousePos.y, 350));
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
    this->levelBuilder->SetSpawnMap(this->game->currentLevel);
    this->levelBuilder->HandleCurrentLevelSpawning();

    //switch (this->game->currentLevel)
    //{
    //case 0:
    //    //menu
    //    break;

    ////---------------------------------------------------------------------------------------------------//
    //// LEVEL DIVIDER //----------------------------------------------------------------------------------//
    ////---------------------------------------------------------------------------------------------------//

    //case 1:
    //    if (this->currentLevelFrameCount % 30 == 0 && this->currentLevelFrameCount < 240)
    //    {
    //        BatEnemy* s = new BatEnemy();
    //        s->SetPosition((float)screenWidth, 500);
    //        s->SetAmplitude(3.0f);
    //        s->upStart = true;
    //        this->game->enemies.push_back(s);

    //    }
    //    break;

    ////---------------------------------------------------------------------------------------------------//
    //// LEVEL DIVIDER //----------------------------------------------------------------------------------//
    ////---------------------------------------------------------------------------------------------------//

    //case 2:
    //    if (this->currentLevelFrameCount % 30 == 0)
    //    {
    //        SoldierEnemy* s = new SoldierEnemy();
    //        s->SetPosition((float)screenWidth, (float)GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
    //        this->game->enemies.push_back(s);
    //    }

    //    if (this->currentLevelFrameCount % 500 == 0)
    //    {
    //        KoopaEnemy* k = new KoopaEnemy();
    //        k->SetPosition((float)screenWidth, (float)GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
    //        this->game->enemies.push_back(k);
    //    }

    //    if (this->currentLevelFrameCount % 400 == 0)
    //    {
    //        RedKoopaEnemy* k = new RedKoopaEnemy();
    //        k->SetPosition((float)screenWidth, (float)GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
    //        this->game->enemies.push_back(k);
    //    }

    //    if (this->currentLevelFrameCount % 410 == 0)
    //    {
    //        WolfEnemy* k = new WolfEnemy();
    //        k->SetPosition((float)screenWidth, (float)GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
    //        this->game->enemies.push_back(k);
    //    }

    //    if (this->currentLevelFrameCount % 300 == 0)
    //    {
    //        BatEnemy* s = new BatEnemy();
    //        s->SetPosition((float)screenWidth, (float)GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
    //        s->SetAmplitude(GetRandomFloat(1, 10));
    //        if (GetRandomValue(1, 2) == 1) s->upStart = true;
    //        this->game->enemies.push_back(s);
    //    }
    //    break;

    ////---------------------------------------------------------------------------------------------------//
    //// LEVEL DIVIDER //----------------------------------------------------------------------------------//
    ////---------------------------------------------------------------------------------------------------//  

    //default:
    //    std::cout << "WARNING: Level " << this->game->currentLevel << " does not exist.";
    //    break;
    //}
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

    //draw firebullet on fire
    for (Bullet* b : g->bullets)
    {
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
