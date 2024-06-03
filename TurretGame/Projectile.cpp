#include "Projectile.h"

void Projectile::Draw() // default draw is a circle. ONLY FOR DEBUG
{
	DrawCircle(this->position.x, this->position.y, 10, BLACK); //temp
}

void Projectile::Update(unsigned int frame) // default is pos and velocty update
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
