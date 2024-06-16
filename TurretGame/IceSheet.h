#pragma once

#include "AreaEffect.h"

class Enemy;

class IceSheet : public AreaEffect
{
public:
	IceSheet(int posX, int posY, int frames); //middle of sheet

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;

	bool EnemyCollided(Enemy* e);
	Rectangle GetHitbox() const;

	int width;
	int height;

private:
	Rectangle hitbox;
	float alphaModifier;
	int totalFrames;
};