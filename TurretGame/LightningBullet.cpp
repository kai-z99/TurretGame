#include "LightningBullet.h"

#include "TextureLoop.h"
#include "textures.h"

LightningBullet::LightningBullet()
{
	this->chain = 0;

	this->id = 5;
	this->baseSpeed = 25.0f;
	this->baseDamage = 25.0f;
	this->baseKnockbackDuration = 0;
	this->hitBoxRadius = 8.0f;
	this->textureLoop = new TextureLoop(&textures[24], 6, 2.0f, this->position);
}

LightningBullet::~LightningBullet()
{
	delete this->textureLoop;
}

void LightningBullet::Draw()
{
	this->textureLoop->Draw();
	//Bullet::Draw();
}

void LightningBullet::Update(unsigned int frame)
{
	Bullet::Update(frame);
	this->textureLoop->SetPosition((int)this->position.x, (int)this->position.y);
	this->textureLoop->Update();

	if (frame % 3 == 0) this->textureLoop->NextFrame();
}
