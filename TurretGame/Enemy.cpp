#include "Enemy.h"
#include "Bullet.h"
#include <iostream>
#include "TextureLoop.h"

Enemy::Enemy()
{
	this->tint = WHITE;
	// for each status effect, set its frames to 0.
	for (int i = 0; i <= 4; i++)
	{
		this->statusEffects[static_cast<StatusEffect>(i)] = 0;
	}
}

Enemy::~Enemy()
{
	delete this->textureLoop;
}

void Enemy::Draw() //draws hitbox
{
	DrawRectangleLines(this->hitbox.x, this->hitbox.y, this->hitbox.width, this->hitbox.height, RED);
}

void Enemy::Update(unsigned int frame)
{

	this->position.x += this->currentVelocity.x;
	this->position.y += this->currentVelocity.y;
	

	if (this->knockbackFrames > 0)
	{
		this->position.x += 9 * this->knockbackMultiplier;
		this->knockbackFrames -= 1;
	}
	
	//for eevery status effect
	for (auto& effect : this->statusEffects)
	{
		//if it active
		if (effect.second > 0)
		{
			switch (effect.first)
			{
			case Burning:
				//-1 hp 2 times per second
				if (frame % 30 == 0) this->health -= 1;
				this->tint = ORANGE;

				effect.second -= 1;
				if (effect.second <= 0) this->tint = WHITE;
				break;

			case Chilled:
				//slow movement
				this->currentVelocity.x = this->baseVelocity.x * 0.3f;
				this->currentVelocity.y = this->baseVelocity.y * 0.3f;
				this->tint = BLUE; //tint blue 

				effect.second -= 1;
				if (effect.second <= 0)
				{
					this->currentVelocity = this->baseVelocity;
					this->tint = WHITE;
				}
				break;
			}

		}
	}

	this->textureLoop->SetTint(this->tint);
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

void Enemy::ApplyKnockback(int frames)
{
	this->knockbackFrames += frames;
}

void Enemy::ApplyStatusEffect(StatusEffect effect, int frames)
{
	this->statusEffects[effect] = frames;
}

std::unordered_map<StatusEffect, int>& Enemy::GetStatusEffects()
{
	return this->statusEffects;
}

void Enemy::SetPosition(float x, float y)
{
	this->position = { x,y };
}

void Enemy::SetCurrentVelocity(float x, float y)
{
	this->currentVelocity = { x,y };
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

Vector2 Enemy::GetBaseVelocity() const
{
	return this->baseVelocity;
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


