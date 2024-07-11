#pragma once

#include "Bullet.h"

class TextureLoop;

class LightningBullet : public Bullet
{
public:
	LightningBullet(Turret* owner);
	~LightningBullet();
	virtual void Draw() override;
	virtual void Update(unsigned int frame) override;

private:
	int chain;
	TextureLoop* textureLoop;

};