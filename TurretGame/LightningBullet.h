#pragma once

#include "Bullet.h"

class LightningBullet : public Bullet
{
public:
	LightningBullet();
	virtual void Draw() override;
	virtual void Update(unsigned int frame) override;

private:
	int chain;

};