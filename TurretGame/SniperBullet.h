#pragma once

#include "Bullet.h"


class SniperBullet : public Bullet
{
public:
	SniperBullet();
	virtual void Draw() override;
	virtual void Update(unsigned int frame) override;
};