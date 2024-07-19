#pragma once

#include "Enemy.h"

#include "constants.h"

class WizardBossEnemyP1 : public Enemy
{
public:
	WizardBossEnemyP1();

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;

	int GetPhase() const;

	std::pair<Vector2, Vector2> GetBulletSpawnInstructions(); // Position, Velocity. based on position and mode

	bool isShootFrame;
	bool fireWithBullet;
	bool isBurstFrame;

	friend class WizardBulletEnemy;

private:

	void HandleMovement();
	void HandleModeSwitching();
	void HandleShooting();
	void HandlePhaseSwitching();

	float speed;
	unsigned int localFramecount;
	unsigned int modeFramecount; //how manh frames past since mode switch
	
	int phase;
	int mode;
	int timesCrossed; // for mode 1

	Vector2 crossVelocity;
	Vector2 fallVelocity;
	Vector2 ascendVelocity;

	const Vector2 basePosition = {(float)halfwayLevelX, (float)halfwayLevelY};
	const Vector2 fallStartPosition = { (float)screenWidth - 300.0f, -200.0f };

	TextureLoop* p2Texture;
};