#include "BalloonBulletEnemy.h"

#include "textures.h"
#include "TextureLoop.h"

BalloonBulletEnemy::BalloonBulletEnemy()
{
	this->id = 8;
	this->damage = 5;
	this->maxHealth = 80.0f;
	this->health = this->maxHealth;
	this->coinDropAmount = GetRandomValue(1, 2);

	this->knockbackMultiplier = 0.0f;
	this->baseVelocity = { -5.5,0.0f };
	this->currentVelocity = this->baseVelocity;
	this->hitbox = { this->position.x - (40 / 2), this->position.y - (40 / 2), 40, 40 };
	this->textureLoop = new TextureLoop(&textures[32], 5, 8.0f, this->position);

	//this->resistChill = true;
}

void BalloonBulletEnemy::Update(unsigned int frame)
{
	// update position and velocity and check if death
	Enemy::Update(frame);

	//update postion of texture
	this->textureLoop->SetPosition((int)this->position.x, (int)this->position.y);

	//update the animation state
	if (frame % 5 == 0) this->textureLoop->NextFrame();

	//update hitbox position
	//this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 100 };
	this->hitbox.x = this->position.x - (40 / 2.0f);
	this->hitbox.y = this->position.y - (40 / 2.0f);

	//update texture proteries based on new position
	this->textureLoop->Update();
}

void BalloonBulletEnemy::Draw()
{
	this->textureLoop->Draw();
	//Enemy::Draw();
	//DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, 0, WHITE);
	//if (this->health < this->maxHealth) this->DrawHealthbar(50, 1.0f);
}

void BalloonBulletEnemy::SetFast()
{
	this->currentVelocity.x = -6.8f;
	this->tint = ORANGE;
}
