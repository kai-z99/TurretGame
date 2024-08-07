#pragma once
#include "Bullet.h"


class Turret;

class FireBullet : public Bullet
{
public:
	FireBullet(Turret* owner);
	virtual void Draw() override;
	virtual void Update(unsigned int frame) override;
};