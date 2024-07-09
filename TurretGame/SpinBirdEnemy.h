#pragma once

#include "Enemy.h"

class BalloonBossEnemy;

class SpinBirdEnemy : public Enemy
{
public:
	SpinBirdEnemy(BalloonBossEnemy* host);

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;

private:
	BalloonBossEnemy* host;

};