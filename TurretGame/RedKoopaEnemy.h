#pragma once
#include "Enemy.h"

class RedKoopaEnemy : public Enemy
{
public:
	RedKoopaEnemy();

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;

private:
	TextureLoop* shellTextureLoop;
	bool shellForm;
	int distanceWalked;
	int deShellThreshold;
};
