#pragma once

#include "Bullet.h"

class Turret;

class BombBullet : public Bullet
{
public:
	BombBullet(Turret* owner);
	virtual void Draw() override;
	virtual void Update(unsigned int frame) override;

private:
	Color tint;
};