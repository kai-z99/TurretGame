#include "TurretBullet.h"
#include "textures.h"
#include "helpers.h"
TurretBullet::TurretBullet()
{
	this->id = 1;
	this->baseSpeed = 30.0f;
	this->baseDamage = 1.0f;
	this->baseKnockbackDuration = 4;
	this->hitBoxRadius = 10.0f;

	//Texture init
	this->texture = &textures[2];
	this->textureWidth = this->texture->width;
	this->textureHeight = this->texture->height;
	this->textureSourceRec = { 0.0f, 0.0f, (float)this->textureWidth, (float)this->textureHeight };
	this->textureDestRec = { this->position.x, this->position.y, (float)this->textureWidth * 0.75f, (float)this->textureHeight * 0.75f };
	this->textureOriginPoint = { this->textureWidth / 2.0f, this->textureHeight / 2.0f };

}

void TurretBullet::Draw() // sould draw sprite
{
	//DrawCircle(this->position.x, this->position.y, this->hitBoxRadius, GRAY);
	DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, this->angle * RAD2DEG, WHITE);
	//Bullet::Draw(); // hitbopxc for debug
}

void TurretBullet::Update(unsigned int frame)
{
	Bullet::Update(frame);

	//update the destination rectangle
	this->textureDestRec = { this->position.x, this->position.y,
						 (float)this->textureWidth * 0.75f,
						 (float)this->textureHeight * 0.75f };

}

