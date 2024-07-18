#pragma once

#include "Enemy.h"


class WizardBulletEnemy : public Enemy
{
public:
	WizardBulletEnemy();

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;

	bool ignited;

private:
	TextureLoop* startLoop;
	unsigned int localFramecount;

	int flippedFrame;//to prevent rapid flipping
};