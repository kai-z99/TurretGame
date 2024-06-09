#include "VisualEffectsManager.h"
#include "CoinSplashEffect.h"
#include "ExplosionEffect.h"
#include "FireEffect.h"


VisualEffectsManager::VisualEffectsManager()
{
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

void VisualEffectsManager::UpdateAndDraw()
{
	for (const auto& element : this->tasks) 
	{
		element->UpdateAndDraw();
	}
}
