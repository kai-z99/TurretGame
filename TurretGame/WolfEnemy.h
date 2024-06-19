#pragma once

#include "Enemy.h"

class WolfEnemy : public Enemy
{
public:
	WolfEnemy();

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;

private:
	int runThreshold;
	int runFrames;
	bool ran;

	float runSpeed;

	TextureLoop* runTexture;
};