#include "ShockwaveBullet.h"

ShockwaveBullet::ShockwaveBullet()
{
	this->id = 2;
	this->baseSpeed = 15.0f;
	this->baseDamage = 2.0f;
	this->baseKnockbackDuration = 20;
	this->hitBoxRadius = 20.0f;
}

void ShockwaveBullet::Draw()
{
	Bullet::Draw(); //hitbox only for now
}

void ShockwaveBullet::Update()
{
	Bullet::Update();
}
