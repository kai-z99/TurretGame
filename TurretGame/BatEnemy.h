#pragma once


#include "Enemy.h"

class BatEnemy : public Enemy
{
public:
	BatEnemy();

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;

private:
	unsigned int localFrameCount;
};