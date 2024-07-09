#pragma once

#include "Enemy.h"
#include "constants.h"

class TextureLoop;

class BalloonBossEnemy : public Enemy
{
public:
	BalloonBossEnemy();

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;

	int GetPhase() const;
	bool isShootFrame;
	bool spawnedShield;

	friend class SpinBirdEnemy;
private:
	void HandleMovement();
	void HandleModeSwitching();
	void HandleShooting();

	unsigned int localFrameCount;
	unsigned int rotateFrameCount;
	int mode; //0: walk 

	float speed;
	Vector2 ascendVelocity;
	Vector2 retreatVelocity;

	int cyclesComplete;
	int phase;
	
	int readyShootFrames;

	const Vector2 basePosition = { (float)screenWidth, (screenHeight / 2) + (menuBoundaryY / 2) };

	TextureLoop* shootLoop;
};