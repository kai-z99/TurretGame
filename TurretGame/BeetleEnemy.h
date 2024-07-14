#pragma once

#include "Enemy.h"

class TextureLoop;

class BeetleEnemy : public Enemy
{
public:
	BeetleEnemy();

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;

private:
	unsigned int localFramecount;

	void HandleDirectionSwitch();

	bool isFacingUp() const;
	int timesSwitched;

	TextureLoop* upLoop;


	
};