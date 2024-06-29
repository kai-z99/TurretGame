#pragma once

#include "AreaEffect.h"

class Enemy;

class IceSheet : public AreaEffect
{
public:
	IceSheet(int posX, int posY); //middle of sheet

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;

	bool EnemyCollided(Enemy* e);
	Rectangle GetHitbox() const;

	static int width;
	static int height;
	static int duration;  // how long the sheet itself lasts
	static int intensity; // how many frames the chill effect is applied for

private:
	Rectangle hitbox;
	float alphaModifier;
};