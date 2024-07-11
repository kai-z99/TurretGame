#include "BombBullet.h"

#include "textures.h"

BombBullet::BombBullet(Turret* owner)
{
	this->id = 6;
	this->baseSpeed = 40.0f;
	this->baseDamage = 95.0f;
	this->baseKnockbackDuration = 0;
	this->hitBoxRadius = 14.0f;

	//Texture init
	this->texture = &textures[2];
	this->textureWidth = this->texture->width;
	this->textureHeight = this->texture->height;
	this->textureSourceRec = { 0.0f, 0.0f, (float)this->textureWidth, (float)this->textureHeight };
	this->textureDestRec = { this->position.x, this->position.y, 30, 30 };
	this->textureOriginPoint = { 30 / 2.0f, 30 / 2.0f };

	this->owner = owner;
	this->tint = DARKGRAY;
}

void BombBullet::Draw()
{
	DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, this->angle * RAD2DEG, this->tint);
	//Bullet::Draw(); // hitbopxc for debug

}

void BombBullet::Update(unsigned int frame)
{
	Bullet::Update(frame);

	//update the destination rectangle
	this->textureDestRec = { this->position.x, this->position.y,
						 30,
						 30 };

	if (frame % 8 == 0)
	{
		//if its currently red, turn white
		if (this->tint.r == 230) this->tint = DARKGRAY;
		//else turn red
		else this->tint = RED;
	}
}


