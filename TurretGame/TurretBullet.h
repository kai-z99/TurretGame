#pragma once
#include "Bullet.h"

class Turret;

class TurretBullet : public Bullet
{
public:
	TurretBullet(Turret* owner);
	virtual void Draw() override; 
	virtual void Update(unsigned int frame) override;

private:
	
};