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
		delete this->textureLoop;
	}
}

void Enemy::DrawHealthbar(int yOffset, float barSize)
{
	int barWidth = 30 * barSize;
	int barHeight = 3 * barSize;

	DrawRectangle(this->position.x - (barWidth / 2), this->position.y - yOffset, barWidth, barHeight, RED);
	DrawRectangle(this->position.x - (barWidth / 2), this->position.y - yOffset, barWidth * (this->health / this->maxHealth), barHeight, GREEN);
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

float Enemy::GetMaxHealth()
{
	return this->maxHealth;
}

int Enemy::GetDamage() const
{
	return this->damage;
}

int Enemy::GetCoinDropAmount() const
{
	return this->coinDropAmount;
}


