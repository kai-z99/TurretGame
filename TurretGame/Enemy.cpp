#include "Enemy.h"
#include "Bullet.h"
#include <iostream>
#include "TextureLoop.h"
#include "constants.h"

Enemy::Enemy()
{
	this->tint = WHITE;
	this->movementChilled = false;
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
	DrawRectangleLines((int)this->hitbox.x, (int)this->hitbox.y, (int)this->hitbox.width, (int)this->hitbox.height, RED);
}

void Enemy::Update(unsigned int frame)
{
	//for eevery status effect
	for (auto& [effect,frames] : this->statusEffects)
	{
		//if it active
		if (frames > 0)
		{
			switch (effect)
			{
			case Burning:
				//-10 hp 2 times per second
				if (frame % 30 == 0) this->health -= 10.0f;
				frames -= 1;
				break;

			case Chilled:
				//slow movement
				this->movementChilled = true;
				if (!this->resistChill) this->tint = BLUE; //tint blue 

				frames -= 1;
				if (frames <= 0)
				{
					this->movementChilled = false;
					if (!this->resistChill) this->tint = WHITE;
				}
				break;
			}

		}
	}

	//MOVE

	if (!this->movementChilled || this->resistChill)
	{
		this->position.x += this->currentVelocity.x;
		this->position.y += this->currentVelocity.y;
	}

	else
	{
		this->position.x += this->currentVelocity.x * 0.3f;
		this->position.y += this->currentVelocity.y * 0.3f;
	}
	
	//KB
	if (this->knockbackFrames > 0)
	{
		this->position.x += 9 * this->knockbackMultiplier;
		this->knockbackFrames -= 1;
	}

	this->textureLoop->SetTint(this->tint);
}

void Enemy::DrawHealthbar(int yOffset, float barSize)
{
	float barWidth = 30 * barSize;
	float barHeight = 3 * barSize;

	DrawRectangle((int)(this->position.x - (barWidth / 2)), (int)(this->position.y - yOffset), (int)barWidth, (int)barHeight, RED);
	DrawRectangle((int)(this->position.x - (barWidth / 2)), (int)(this->position.y - yOffset), (int)(barWidth * (this->health / this->maxHealth)), (int)barHeight, GREEN);
}

void Enemy::DrawBossHealthbar(const char* title, Color barColor, Color textColor)
{
	int barWidth = 1200;
	int barHeight = 50;

	DrawRectangle((int)((screenWidth / 2.0f) + (deathBoundaryX / 2.0f) - (barWidth / 2.0f) - 5), 1000 - 5, barWidth + 10, barHeight + 10, BLACK);
	DrawRectangle((int)((screenWidth / 2.0f) + (deathBoundaryX / 2.0f) - (barWidth / 2.0f)), 1000, (int)barWidth, (int)barHeight, RED);
	DrawRectangle((int)((screenWidth / 2.0f) + (deathBoundaryX / 2.0f) - (barWidth / 2.0f)), 1000, (int)(barWidth * (this->health / this->maxHealth)), (int)barHeight, barColor);

	int textWidth = MeasureText(title, 30);
	DrawText(title, (int)((screenWidth / 2.0f) + (deathBoundaryX / 2.0f) - (barWidth / 2.0f)), 960, 30, textColor);
}

void Enemy::DrawShadow(int yOffset, int xOffset, float scale)
{
	DrawEllipse((int)this->position.x + xOffset, (int)this->position.y + (int)(this->textureLoop->GetDestDimensions().y / 2) + yOffset, 49 * scale, 21 * scale, {0,0,0,100});
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

void Enemy::AppendStatusEffect(StatusEffect effect, int frames)
{
	this->statusEffects[effect] += frames;
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

void Enemy::SetBaseVelocity(float x, float y)
{
	this->baseVelocity = { x,y };
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


