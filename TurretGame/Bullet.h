#pragma once
#include "Projectile.h"

class Enemy;

class Bullet : public Projectile
{
public:
	virtual void Draw() override;
	bool EnemyCollided(Enemy* e);

	float GetBaseSpeed() const;

protected:
	float baseDamage;
	float baseSpeed;
	float hitBoxRadius;
};