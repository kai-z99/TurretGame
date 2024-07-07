#pragma once

#include "Enemy.h"
#include "constants.h"

class BalloonBossEnemy : public Enemy
{
public:
	BalloonBossEnemy();

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;

private:
	void HandleMovement();

	unsigned int localFrameCount;
	unsigned int rotateFrameCount;
	int mode; //0: walk 

	float speed;
	Vector2 ascendVelocity;
	Vector2 retreatVelocity;

	int cyclesComplete;
	int phase;

	const Vector2 basePosition = { (float)screenWidth, (screenHeight / 2) + (menuBoundaryY / 2) };
};