#pragma once

#include "AreaEffect.h"

class Enemy;

class BombExplosion : public AreaEffect
{
public:
	BombExplosion(int posX, int posY, bool bullet);

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;

	bool EnemyCollided(Enemy* e);

	bool isBullet;
	bool isDetonateFrame;

	static float damage;
	static int knockbackFrames;
	static float radius;
	static float bulletRadius;

	int animSpeed;
};