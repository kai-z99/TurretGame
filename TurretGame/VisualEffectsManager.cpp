#include "VisualEffectsManager.h"
#include "CoinSplashEffect.h"
#include "ExplosionEffect.h"
#include "FireEffect.h"
#include "IceSparkleEffect.h"

#include <iostream>


VisualEffectsManager::VisualEffectsManager()
{
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

void VisualEffectsManager::DisplayIceSparkle(Vector2 pos, float scale)
{
    VisualEffect* v = new IceSparkleEffect(pos, scale);
    this->tasks.push_back(v);
}


void VisualEffectsManager::UpdateAndDraw()
{
    if (this->tasks.size() > 700) this->CleanTasks();

	for (VisualEffect* element : this->tasks) 
	{
		element->UpdateAndDraw();
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

