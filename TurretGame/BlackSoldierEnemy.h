#pragma once

#include "Enemy.h"


class BlackSoldierEnemy : public Enemy
{
public:
	BlackSoldierEnemy();

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;

private:
};