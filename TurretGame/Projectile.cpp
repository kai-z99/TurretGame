#include "Projectile.h"

void Projectile::Draw() // default draw is a circle. ONLY FOR DEBUG
{
	DrawCircle((int)this->position.x, (int)this->position.y, 10, BLACK); //temp
}

void Projectile::Update(unsigned int frame) // default is pos and velocty update
{
	this->position.x += this->currentVelocity.x;
	this->position.y += this->currentVelocity.y;
}

Vector2 Projectile::GetPosition() const
{
	return this->position;
}

void Projectile::SetPosition(float x, float y)
{
	this->position = { x , y };
}

void Projectile::SetCurrentVelocity(float x, float y)
{
	this->currentVelocity = { x , y };
}
