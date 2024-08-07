#include "ShockwaveBullet.h"
#include "textures.h"
#include "helpers.h"


ShockwaveBullet::ShockwaveBullet(Turret* owner)
{
	this->id = 2;
	this->baseSpeed = 35.0f;
	this->baseDamage = 35.0f;
	this->baseKnockbackDuration = 20;
	this->hitBoxRadius = 20.0f;

	//Texture init
	this->texture = &textures[7];
	this->textureWidth = this->texture->width;
	this->textureHeight = this->texture->height;
	this->textureSourceRec = { 0.0f, 0.0f, (float)this->textureWidth, (float)this->textureHeight };
	this->textureDestRec = { this->position.x, this->position.y, (float)this->textureWidth, (float)this->textureHeight};
	this->textureOriginPoint = { this->textureWidth / 2.0f, this->textureHeight / 2.0f };

	this->owner = owner;
}

void ShockwaveBullet::Draw()
{
	
	DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, this->angle * RAD2DEG, WHITE);
	//Bullet::Draw(); //hitbox 
}

void ShockwaveBullet::Update(unsigned int frame)
{
	Bullet::Update(frame);

	//update the destination rectangle
	this->textureDestRec = { this->position.x, this->position.y,
						 (float)this->textureWidth,
						 (float)this->textureHeight};
}
