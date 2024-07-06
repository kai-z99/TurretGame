#include "TurretBullet.h"
#include "textures.h"
#include "helpers.h"
TurretBullet::TurretBullet()
{
	this->id = 1;
	this->baseSpeed = 40.0f;
	this->baseDamage = 15.0f;
	this->baseKnockbackDuration = 2;
	this->hitBoxRadius = 10.0f;

	//Texture init
	this->texture = &textures[28];
	this->textureWidth = this->texture->width;
	this->textureHeight = this->texture->height;
	this->textureSourceRec = { 0.0f, 0.0f, (float)this->textureWidth, (float)this->textureHeight };
	this->textureDestRec = { this->position.x, this->position.y, (float)this->textureWidth * 0.2f, (float)this->textureHeight * 0.2f };
	this->textureOriginPoint = { this->textureWidth * 0.2f / 2.0f, this->textureHeight * 0.2f / 2.0f };
}

void TurretBullet::Draw() // sould draw sprite
{
	Color tint = WHITE;
	DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, this->angle * RAD2DEG, tint);
	//Bullet::Draw(); // hitbopxc for debug
}

void TurretBullet::Update(unsigned int frame)
{
	Bullet::Update(frame);

	//update the destination rectangle
	this->textureDestRec = { this->position.x, this->position.y,
						 (float)this->textureWidth * 0.2f,
						 (float)this->textureHeight * 0.2f };

}

