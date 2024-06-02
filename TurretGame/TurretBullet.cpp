#include "TurretBullet.h"

TurretBullet::TurretBullet()
{
	this->baseSpeed = 20.0f;
	this->baseDamage = 1.0f;
	this->hitBoxRadius = 10.0f;
}

void TurretBullet::Draw() // sould draw sprite
{
	DrawCircle(this->position.x, this->position.y, this->hitBoxRadius, GRAY);
}
