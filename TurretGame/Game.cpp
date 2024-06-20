#include "Game.h"
#include <iostream>
#include <string>
#include "Turret.h"
#include "Enemy.h"
#include "Bullet.h"
#include "TurretBullet.h"
#include "Hotbar.h"
#include "textures.h"
#include "helpers.h"
#include "VisualEffectsManager.h"
#include "types.h"
#include "BombExplosion.h"
#include "IceSheet.h"
#include "RedKoopaEnemy.h"
#include "LevelHandler.h"

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
        this->Update();
        this->HandleEnemySpawning();
        //this->HandleCollisions();
        this->HandleInput();
        this->Draw();
    }

    CloseWindow();
}

void Game::CleanVectors()
{
    for (Enemy* e : this->enemies)
    {
        delete e;
    }

    for (Bullet* b : this->bullets)
    {
        delete b;
    }

    for (AreaEffect* a : this->areaEffects)
    {
        delete a;
    }

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
    
    this->currentLevel = 2;

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
    this->levelHandler->HandleLevelExit();

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
    //draw bg
    DrawTexture(textures[6], 0, 0, WHITE);

    //draw boundaries
    DrawLine(deathBoundaryX, 0, deathBoundaryX, screenHeight, RED);
    DrawLine(0, menuBoundaryY, screenWidth, menuBoundaryY, RED);

    //draw turret
    this->turret->Draw();

    //DRAW ICE UNDER
    for (AreaEffect* a : this->areaEffects)
    {
        //id 2 is ice
        if (a->isActive && a->GetID() == 2) a->Draw();
    }

    //draw enemies based on type. elsewise default enemy drawing behavoir.
    for (Enemy* e : this->enemies)
    {
        if (e->isActive) e->Draw();
    }

    //draw bullets based on type. elsewise default enemy drawing behavoir.
    for (Bullet* b : this->bullets)
    {
        if (b->isActive) b->Draw();
    }

    //DRAW EXPLOSION ON TOP
    for (AreaEffect* a : this->areaEffects)
    {
        //id 1 is bomb
        if (a->isActive && a->GetID() != 2) a->Draw();
    }

    //draw rolling effects
    this->DrawVisualEffects();

    //update and draw the effects that are on screen
    this->effectManager->UpdateAndDraw();

    //draw hotbar
    this->hotbar->Draw(*this->levelHandler->currentLevelStats);
}

//THIS SHOULD BE IN VISUAL EFFECTS MANAGER.
void Game::DrawVisualEffects()
{
    //--------------
    //FIRE EFFECTS

    //draw burning enemies on fire
    for (Enemy* e : enemies)
    {
        if (e->isActive && e->GetStatusEffects()[Burning] % 8 == 7) effectManager->DisplayFire(e->GetPosition(), 1.0f);
    }


    //draw firebullet on fire
    for (Bullet* b : bullets)
    {
        if (b->isActive && b->GetID() == 3 && this->frameCount % 2 == 0)
        {
            Vector2 firePos = b->GetPosition();
            firePos.y -= 10;
            firePos.x -= 10;

            //make it look a bit more sparratic
            firePos.y += GetRandomValue(-5, 5);

            float scaleMod = GetRandomValue(-100, 100) * 0.0015f;

            effectManager->DisplayFire(firePos, 0.5f + scaleMod);
        }
    }

    //draw sparkles on ice sheet
    for (AreaEffect* a : this->areaEffects)
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


            this->effectManager->DisplayIceSparkle(pos, GetRandomValue(-100, 100) * 0.02f);
        }
    }
}


void Game::Update()
{
    //update frame
	this->frameCount++;

    //update mouse position
    mousePos = { GetMousePosition().x, GetMousePosition().y };

    

    //split this in future
    // 
    //-----------------------------------------------------------------------
    // IN GAME UPDATE //
    //-----------------------------------------------------------------------

    this->levelHandler->Update(this->frameCount);

    //update hotbar buttons
    if (this->hotbar != nullptr) this->hotbar->Update(this->frameCount, this->levelHandler->currentLevelStats->abilityStates);

    //if an ability button is pressed, activate its ability if it has a charge.
    this->ActivateUsedAbilities();

    //update turret
    this->turret->Update(frameCount, (int)mousePos.x, (int)mousePos.y);

    //handle bullets
	for (Bullet* b : this->bullets)
	{
        if (b->isActive) b->Update(this->frameCount);
	}

    for (AreaEffect* a : this->areaEffects)
    {
        if (a->isActive) a->Update(this->frameCount);
    }

    //handle enemies
	for (Enemy* e : this->enemies)
	{
        if (e->isActive)
        {
            e->Update(this->frameCount); //move enemy, apply effects, apply knockback. apply tint

            // if enemy died, add coin amount. and display coin effect
            if (e->GetHealth() <= 0)
            {
                this->levelHandler->currentLevelStats->coinsCollected += e->GetCoinDropAmount();
                this->effectManager->DisplayCoinSplash(e->GetPosition(), e->GetCoinDropAmount());
                e->isActive = false;
            }

            //check if enemy has infiltrated the base
            else if (e->GetPosition().x <= deathBoundaryX)
            {
                this->levelHandler->currentLevelStats->health -= e->GetDamage();
                e->isActive = false;
            }
        }
		
	}

    //handle collisions
    this->HandleCollisions();

    //CHECK HERE IF ENEMY VECTOR IS TOO BIG. IF IT IS, CLEAN IT.
    //SAME AS AOE HERE

    //-----------------------------------------------------------------------
    // MENU UPDATE //
    //-----------------------------------------------------------------------
}


//helper for update
void Game::ActivateUsedAbilities()
{
    //if an ability button is pressed, activate its ability if it has a charge and it is not on cooldown

    //go through every ablity that was clicked this frame
    for (const TurretAbility& a : this->hotbar->GetActiveAbilityButtons())
    {
        //info of the current ability
        AbilityInfo& info = this->levelHandler->currentLevelStats->abilityStates[a];

        // if the ability is ready,
        if (this->frameCount - info.lastUsedFrame >= info.cooldown)
        {
            //if there is an availible chrage, use one.
            if (info.charges > 0)
            {
                info.charges -= 1;
                info.lastUsedFrame = this->frameCount;

                switch (a)
                {
                case Rapidfire:
                    this->turret->SetRapidFire(240);
                    break;

                case SpecialRapidfire:
                    this->turret->SetSpecialRapidfire(240);
                    break;

                case Explosive:
                    this->inputMode = 1; //1 is bomb place mode
                    break;

                case Ice:
                    this->inputMode = 2; //2 is ice mode
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


void Game::HandleCollisions()
{
    //bullet collisions
    for (Bullet* b : this->bullets)
    {
        if (b->isActive)
        {
            for (Enemy* e : enemies)
            {
                if (e->isActive && b->EnemyCollided(e)) //if collide, remove buullet and deal damage
                {
                    this->HandleBulletCollideEnemy(e,b);
                }
                
            }
        }
    }

    //AOE collisions
    for (AreaEffect* a : this->areaEffects)
    {
        if (a->isActive)
        {
            switch (a->GetID())
            {
            //BOMB EXPLOSTION
            case 1:
                for (Enemy* e : enemies)
                {
                    BombExplosion* exp = dynamic_cast<BombExplosion*>(a);
                    if (e->isActive && exp->isDetonateFrame && exp->EnemyCollided(e))
                    {
                        e->SetHealth(e->GetHealth() - exp->GetDamage());
                        e->ApplyKnockback(exp->GetKnockbackFrames());
                    }
                }

                break;

            //ice sheet
            case 2:
                for (Enemy* e : enemies)
                {
                    IceSheet* i = dynamic_cast<IceSheet*>(a);
                    if (e->isActive && i->isActive && i->EnemyCollided(e))
                    {
                        //id 3 is red koopa
                        if (e->GetID() != 3) e->ApplyStatusEffect(Chilled, 150);
                        //only chill when its not in shell
                        else if (!dynamic_cast<RedKoopaEnemy*>(e)->shellForm) e->ApplyStatusEffect(Chilled, 150);
                    }
                }

                break;


            default:
                break;
            }
        }
    }
}

void Game::HandleBulletCollideEnemy(Enemy* e, Bullet* b)
{
    //display the explosion
    this->effectManager->DisplayExplosion(b->GetPosition());

    //DAMAGE AND KNOCKBACK
    switch (e->GetID())
    {
    //RED KOOPA
    case 3:
        //only apply dmg and kb if not in shell
        if (dynamic_cast<RedKoopaEnemy*>(e)->shellForm) break;

    default:
        e->SetHealth(e->GetHealth() - b->GetBaseDamage());
        e->ApplyKnockback(b);
        break;

    }

    //STATUS EFFECT
    switch (b->GetID())
    {
    // fire bullet
    case 3:
        //apply burning for 4 seconds if not a red koopa
        if (e->GetID() != 3)
        {
            e->ApplyStatusEffect(Burning, 240);
            break;
        }
        
        //dont apply burn if red koopa in shell
        else if (!dynamic_cast<RedKoopaEnemy*>(e)->shellForm)
        {
            e->ApplyStatusEffect(Burning, 240);
        }
        break;

    default:
        break;
    }

    b->isActive = false;
}

void Game::HandleInput()
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
    this->levelHandler->HandleCurrentLevelSpawning();  
}

