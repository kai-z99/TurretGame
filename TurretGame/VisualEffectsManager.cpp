#include "VisualEffectsManager.h"
#include "CoinSplashEffect.h"
#include "ExplosionEffect.h"
#include "FireEffect.h"
#include "BlueFireEffect.h"
#include "IceSparkleEffect.h"
#include "SparkleEffect.h"
#include "WizardSparkleEffect.h"


#include "Game.h"
#include "Bullet.h"
#include "Enemy.h"
#include "WizardBulletEnemy.h"
#include "IceSheet.h"

#include "helpers.h"

#include <iostream>


VisualEffectsManager::VisualEffectsManager(Game* g)
{
    this->game = g;
    this->lightningAlpha = 0;
}

VisualEffectsManager::~VisualEffectsManager()
{
    for (VisualEffect* element : this->tasks)
    {
        delete element;
    }
}

void VisualEffectsManager::DisplayCoinSplash(Vector2 pos, int amount)
{
	VisualEffect* v = new CoinSplashEffect(pos, amount);
	this->tasks.push_back(v);
}

void VisualEffectsManager::DisplayExplosion(Vector2 pos)
{
	VisualEffect* v = new ExplosionEffect(pos);
	this->tasks.push_back(v);
}

void VisualEffectsManager::DisplayFire(Vector2 pos, float scale)
{
	VisualEffect* v = new FireEffect(pos, scale);
	this->tasks.push_back(v);
}

void VisualEffectsManager::DisplayBlueFire(Vector2 pos, float scale)
{
    VisualEffect* v = new BlueFireEffect(pos, scale);
    this->tasks.push_back(v);
}

void VisualEffectsManager::DisplayIceSparkle(Vector2 pos, float scale)
{
    VisualEffect* v = new IceSparkleEffect(pos, scale);
    this->tasks.push_back(v);
}

void VisualEffectsManager::DisplaySparkle(Vector2 pos, float scale)
{
    VisualEffect* v = new SparkleEffect(pos, scale);
    this->tasks.push_back(v);
}

void VisualEffectsManager::DisplayWizardSparkle(Vector2 pos, float scale)
{
    VisualEffect* v = new WizardSparkleEffect(pos, scale);
    this->tasks.push_back(v);
}



void VisualEffectsManager::UpdateAndDraw()
{
    if (this->tasks.size() > this->taskLimit) this->CleanTasks();

	for (VisualEffect* element : this->tasks) 
	{
		element->UpdateAndDraw();
	}

    this->DrawBulletTrails();
    this->DrawIceSheetParticles();
    this->DrawEnemyEmits();
    this->DrawLightning();
}

void VisualEffectsManager::DrawBulletTrails()
{
    Game* g = this->game;
    for (Bullet* b : g->bullets)
    {
        //draw firebullet trail
        if (b->isActive && b->GetID() == 3 && g->frameCount % 2 == 0)
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
        else if (b->isActive && b->GetID() == 4 && g->frameCount % 2 == 0)
        {
            Vector2 sparklePos = b->GetPosition();

            //make it look a bit more sparratic
            sparklePos.y += GetRandomValue(-5, 5);

            float scaleMod = GetRandomValue(-100, 100) * 0.015f;

            g->effectManager->DisplayIceSparkle(sparklePos, 0.5f + scaleMod);
        }

        //electric trail
        else if (b->isActive && b->GetID() == 5 && g->frameCount % 2 == 0)
        {
            Vector2 sparklePos = b->GetPosition();

            //make it look a bit more sparratic
            sparklePos.y += GetRandomValue(-15, 15);

            float scaleMod = GetRandomFloat(-0.4f,0.4f);

            g->effectManager->DisplaySparkle(sparklePos, 2.0f + scaleMod);
        }
    }
}

void VisualEffectsManager::DrawIceSheetParticles()
{
    Game* g = this->game;
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

void VisualEffectsManager::DrawEnemyEmits()
{
    Game* g = this->game;

    //private local frame count
    static int frame = 0;
    frame++;

    for (Enemy* e : g->enemies)
    {
        //draw fire if burning
        if (e->isActive && e->GetStatusEffects()[Burning] % 8 == 7) g->effectManager->DisplayFire(e->GetPosition(), 1.0f);

        
        if (e->isActive && e->GetID() == 12 )
        {
            //particle
            if (frame % 10 == 0)
            {
                Vector2 pos = e->GetPosition();
                pos.x += GetRandomFloat(-10.0f, 10.0f);
                pos.y += GetRandomFloat(-10.0f, 10.0f);
                this->DisplayWizardSparkle(pos, GetRandomFloat(1.5f,3.5f));
            }


            //ignited fire
            if (dynamic_cast<WizardBulletEnemy*>(e)->ignited && frame % 6 == 0)
            {
                this->DisplayBlueFire(e->GetPosition(), 3.0f);
            }


        }


    }
}

void VisualEffectsManager::DrawLightning()
{
    Game* g = this->game;
    //LIGHTNING EFFECT
    if (g->lightningPoints.size() > 1)
    {
        for (int i = 0; i < g->lightningPoints.size() - 1; i++)
        {
            DrawLineEx(g->lightningPoints[i], g->lightningPoints[i + 1], 5.0f, { 255,255,0,(unsigned char)this->lightningAlpha });
        }
    }
}

void VisualEffectsManager::Clear()
{
    for (VisualEffect* v : this->tasks)
    {
        delete v;
    }

    this->tasks.clear();
}

void VisualEffectsManager::CleanTasks() //see clean bullet vector
{
    std::cout << "size before: " << this->tasks.size() << '\n';
    std::vector<VisualEffect*> temp;

    for (VisualEffect* v : this->tasks)
    {
        if (v->isActive())
        {
            temp.push_back(v);
        }

        else delete v;
    }

    this->tasks.clear(); 

    this->tasks.insert(this->tasks.end(), temp.begin(), temp.end());
    std::cout << "size after: " << this->tasks.size() << '\n';
}




