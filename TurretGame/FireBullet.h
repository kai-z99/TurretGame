#pragma once
#include "Bullet.h"

class FireBullet : public Bullet
{
public:
	FireBullet();
	virtual void Draw() override;
	virtual void Update(unsigned int frame) override;
};