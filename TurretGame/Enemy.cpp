#include "Enemy.h"
#include <iostream>

void Enemy::Draw() //draws hitbox
{
	DrawRectangleLines(this->position.x - (this->hitbox.width / 2), this->position.y - (this->hitbox.height / 2), this->hitbox.width, this->hitbox.height, RED);
}

void Enemy::Update(unsigned int frame)
{
	this->position.x += this->velocity.x;
	this->position.y += this->velocity.y;

	if (this->health <= 0)
	{
		this->isActive = false;
	}
}

void Enemy::SetPosition(float x, float y)
{
	this->position = { x,y };
}

void Enemy::SetVelocity(float x, float y)
{
	this->velocity = { x,y };
}

void Enemy::SetHealth(float health)
{
	this->health = health;
}

Rectangle Enemy::GetHitbox() const
{
	return this->hitbox;
}

float Enemy::GetHealth()
{
	return this->health;
}

bool Enemy::IsActive()
{
	return this->isActive;
}
