#pragma once
#include "Bullet.h"


class TurretBullet : public Bullet
{
public:
	TurretBullet();
	virtual void Draw() override; 
};