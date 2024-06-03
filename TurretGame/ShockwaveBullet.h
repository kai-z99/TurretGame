#pragma once

#include "Bullet.h"


class ShockwaveBullet : public Bullet
{
public:
	ShockwaveBullet();
	virtual void Draw() override;
	virtual void Update() override;
};