#pragma once
#include "Bullet.h"

class Turret;

class ShockwaveBullet : public Bullet
{
public:
	ShockwaveBullet(Turret* owner);
	virtual void Draw() override;
	virtual void Update(unsigned int frame) override;
};