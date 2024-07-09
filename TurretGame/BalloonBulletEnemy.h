#pragma once

#include "Enemy.h"


class BalloonBulletEnemy : public Enemy
{
public:
	BalloonBulletEnemy();

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;

	void SetFast();
};