#include "Projectile.h"

void Projectile::Draw()
{
	DrawCircle(this->position.x, this->position.y, 10, BLACK); //temp
}

void Projectile::Update()
{
	this->position.x += this->velocity.x;
	this->position.y += this->velocity.y;
}

void Projectile::SetPosition(float x, float y)
{
	this->position = { x , y };
}

void Projectile::SetVelocity(float x, float y)
{
	this->velocity = { x , y };
}
