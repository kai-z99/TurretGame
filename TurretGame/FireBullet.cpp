#include "FireBullet.h"
#include "textures.h"

FireBullet::FireBullet()
{
	this->id = 3;
	this->baseSpeed = 30.0f;
	this->baseDamage = 64.0f;
	this->baseKnockbackDuration = 1;
	this->hitBoxRadius = 10.0f;

	//Texture init
	this->texture = &textures[18];
	this->textureWidth = this->texture->width;
	this->textureHeight = this->texture->height;
	this->textureSourceRec = { 0.0f, 0.0f, (float)this->textureWidth, (float)this->textureHeight };
	this->textureDestRec = { this->position.x, this->position.y, (float)this->textureWidth * 2.2f, (float)this->textureHeight * 2.2f};
	this->textureOriginPoint = { this->textureWidth * 2.2f / 2.0f, this->textureHeight * 2.2f / 2.0f };
}

void FireBullet::Draw()
{
	//DrawCircle(this->position.x, this->position.y, this->hitBoxRadius, GRAY);
	DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, this->angle * RAD2DEG, WHITE);
	//Bullet::Draw(); // hitbopxc for debug
}

void FireBullet::Update(unsigned int frame)
{
	Bullet::Update(frame);

	//update the destination rectangle
	this->textureDestRec = { this->position.x, this->position.y,
						 (float)this->textureWidth * 2.2f,
						 (float)this->textureHeight * 2.2f };


}