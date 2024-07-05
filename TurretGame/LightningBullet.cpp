#include "LightningBullet.h"
#include "textures.h"

LightningBullet::LightningBullet()
{
	this->chain = 0;

	this->id = 5;
	this->baseSpeed = 20.0f;
	this->baseDamage = 1.0f;
	this->baseKnockbackDuration = 0;
	this->hitBoxRadius = 8.0f;

	//Texture init
	this->texture = &textures[19];
	this->textureWidth = this->texture->width;
	this->textureHeight = this->texture->height;
	this->textureSourceRec = { 0.0f, 0.0f, (float)this->textureWidth, (float)this->textureHeight };
	this->textureDestRec = { this->position.x, this->position.y, (float)this->textureWidth * 2.0f, (float)this->textureHeight * 2.0f };
	this->textureOriginPoint = { this->textureWidth * 2.0f / 2.0f, this->textureHeight * 2.0f / 2.0f };
}

void LightningBullet::Draw()
{
	DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, (PI / 2 + this->angle) * RAD2DEG, YELLOW);
	Bullet::Draw();
}

void LightningBullet::Update(unsigned int frame)
{
	Bullet::Update(frame);

	//update the destination rectangle
	this->textureDestRec = { this->position.x, this->position.y,
						 (float)this->textureWidth * 2.0f,
						 (float)this->textureHeight * 2.0f };

}
