#include "FireBullet.h"
#include "textures.h"

FireBullet::FireBullet()
{
	this->id = 3;
	this->baseSpeed = 25.0f;
	this->baseDamage = 2.0f;
	this->baseKnockbackDuration = 1;
	this->hitBoxRadius = 10.0f;

	//Texture init
	this->texture = &textures[2];
	this->textureWidth = this->texture->width;
	this->textureHeight = this->texture->height;
	this->textureSourceRec = { 0.0f, 0.0f, (float)this->textureWidth, (float)this->textureHeight };
	this->textureDestRec = { this->position.x, this->position.y, (float)this->textureWidth * 0.75f, (float)this->textureHeight * 0.75f };
	this->textureOriginPoint = { this->textureWidth / 2.0f, this->textureHeight / 2.0f };
}

void FireBullet::Draw()
{
	Color tint = RED;
	//DrawCircle(this->position.x, this->position.y, this->hitBoxRadius, GRAY);
	DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, this->angle * RAD2DEG, tint);
	//Bullet::Draw(); // hitbopxc for debug
}

void FireBullet::Update(unsigned int frame)
{
	Bullet::Update(frame);

	//update the destination rectangle
	this->textureDestRec = { this->position.x, this->position.y,
						 (float)this->textureWidth,
						 (float)this->textureHeight };


}