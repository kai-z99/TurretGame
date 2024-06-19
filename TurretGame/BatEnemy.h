#pragma once


#include "Enemy.h"

class BatEnemy : public Enemy
{
public:
	BatEnemy();

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;

	void SetAmplitude(float amplitude);
	bool upStart; //start going up first, else is down first

private:
	unsigned int localFrameCount;
	float amplitude;
	
};