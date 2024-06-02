#pragma once
#include "Enemy.h"

class KoopaEnemy : public Enemy
{
public:
	KoopaEnemy();

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;
};