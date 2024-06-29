#include "SniperBullet.h"
#include "textures.h"

SniperBullet::SniperBullet()
{
	this->id = 4;
	this->baseSpeed = 40.0f;
	this->baseDamage = 5.0f;
	this->baseKnockbackDuration = 10;
	this->hitBoxRadius = 10.0f;

	//Texture init
	this->texture = &textures[19];
	this->textureWidth = this->texture->width;
	this->textureHeight = this->texture->height;
	this->textureSourceRec = { 0.0f, 0.0f, (float)this->textureWidth, (float)this->textureHeight };
	this->textureDestRec = { this->position.x, this->position.y, (float)this->textureWidth * 2.0f, (float)this->textureHeight * 2.0f };
	this->textureOriginPoint = { this->textureWidth * 2.0f / 2.0f, this->textureHeight * 2.0f / 2.0f };
}

void SniperBullet::Draw()
{
	//DrawCircle(this->position.x, this->position.y, this->hitBoxRadius, GRAY);
	DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, (PI / 2 + this->angle) * RAD2DEG, WHITE);
	//Bullet::Draw(); // hitbopxc for debug
}

void SniperBullet::Update(unsigned int frame)
{
	Bullet::Update(frame);

	//update the destination rectangle
	this->textureDestRec = { this->position.x, this->position.y,
						 (float)this->textureWidth * 2.0f,
						 (float)this->textureHeight * 2.0f };


}
