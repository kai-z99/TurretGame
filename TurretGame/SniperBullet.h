#pragma once

#include "Bullet.h"

class Turret;

class SniperBullet : public Bullet
{
public:
	SniperBullet(Turret* owner);
	virtual void Draw() override;
	virtual void Update(unsigned int frame) override;
};