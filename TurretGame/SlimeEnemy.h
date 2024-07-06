#pragma once

#include "Enemy.h"

class SlimeEnemy : public Enemy
{
public:
	SlimeEnemy(bool small);

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;
	bool small;

private:
};