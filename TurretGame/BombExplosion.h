#pragma once

#include "AreaEffect.h"

class Enemy;

class BombExplosion : public AreaEffect
{
public:
	BombExplosion(int posX, int posY);

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;

	bool EnemyCollided(Enemy* e);
	int GetDamage() const;
	int GetKnockbackFrames() const;


	bool isDetonateFrame;



private:
	float hitboxRadius;
	int damage;
	int knockbackFrames;
	
};