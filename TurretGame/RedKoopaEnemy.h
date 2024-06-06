#pragma once
#include "Enemy.h"

class RedKoopaEnemy : public Enemy
{
public:
	RedKoopaEnemy();

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;

	bool shellForm;

private:
	TextureLoop* shellTextureLoop;
	
	int distanceWalked;
	int deShellThreshold;
};
