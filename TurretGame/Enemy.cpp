#include "Enemy.h"
#include <iostream>

void Enemy::Draw() //draws hitbox
{
	DrawRectangleLines(this->hitbox.x, this->hitbox.y, this->hitbox.width, this->hitbox.height, RED);
}

void Enemy::Update(unsigned int frame)
{
	// if inKB is false:
	this->position.x += this->velocity.x; 
	this->position.y += this->velocity.y;

	// else: this->position.x -= bulletKB * enemyKBAmount; inKB will last some variable amount of frames
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

int Enemy::GetID() const
{
	return this->id;
}

Rectangle Enemy::GetHitbox() const
{
	return this->hitbox;
}

Vector2 Enemy::GetPosition() const
{
	return this->position;
}

float Enemy::GetHealth()
{
	return this->health;
}

int Enemy::GetDamage() const
{
	return this->damage;
}

