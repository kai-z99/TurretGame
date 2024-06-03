#include "Enemy.h"
#include "Bullet.h"
#include <iostream>

void Enemy::Draw() //draws hitbox
{
	DrawRectangleLines(this->hitbox.x, this->hitbox.y, this->hitbox.width, this->hitbox.height, RED);
}

void Enemy::Update(unsigned int frame)
{
	if (this->knockbackFrames <= 0)
	{
		this->position.x += this->velocity.x;
		this->position.y += this->velocity.y;
	}

	else
	{
		this->position.x += 5 * this->knockbackMultiplier;
		this->knockbackFrames -= 1;
	}
	
	if (this->health <= 0)
	{
		this->isActive = false;
	}
}

void Enemy::ApplyKnockback(Bullet* b)
{
	this->knockbackFrames += b->GetBaseKnockbackDuration();
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


