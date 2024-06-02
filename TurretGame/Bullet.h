#pragma once
#include "Projectile.h"

class Enemy;

class Bullet : public Projectile
{
public:
	virtual void Draw() override; //default draw is a red circle; debug only
	bool EnemyCollided(Enemy* e);

	float GetBaseSpeed() const;

	bool isActive = true;
	//bool IsActive();
	

protected:
	float baseDamage;
	float baseSpeed;
	float hitBoxRadius;
};