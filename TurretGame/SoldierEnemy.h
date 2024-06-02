#pragma once
#include "Enemy.h"

class SoldierEnemy : public Enemy
{
public:
	SoldierEnemy();

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;
};