#include "RedKoopaEnemy.h"
#include "textures.h"
#include "TextureLoop.h"

RedKoopaEnemy::RedKoopaEnemy()
{
	this->id = 3;
	this->damage = 6;
	this->maxHealth = 500.0f;
	this->health = this->maxHealth;
	this->coinDropAmount = GetRandomValue(20,30);

	this->knockbackMultiplier = 0.0f;
	this->baseVelocity = { -1.2f,0.0f }; //walking speed
	this->currentVelocity = { -4.0f, 0.0f }; //shell speed
	this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 100 }; //50 and 100 are the hitbox dimensions... minus half for centering purpose
	this->textureLoop = new TextureLoop(&textures[4], 4, 4.0f, this->position);
	this->shellTextureLoop = new TextureLoop(&textures[5], 4, 4.0f, this->position);

	//special
	this->distanceWalked = 0;
	this->shellForm = true;
	this->deShellThreshold = GetRandomValue(380, 600);
}

void RedKoopaEnemy::Update(unsigned int frame)
{
	// update position and velocity and check if death
	Enemy::Update(frame);

	//update distance walked
	this->distanceWalked -= (int)this->currentVelocity.x;

	//check if koopa should unshell
	if (this->distanceWalked >= deShellThreshold && this->shellForm)
	{
		this->shellForm = false;
		this->currentVelocity = this->baseVelocity;
		this->knockbackMultiplier = 0.65f;
	}

	//update postion of texture
	this->textureLoop->SetPosition((int)this->position.x, (int)this->position.y);
	this->shellTextureLoop->SetPosition((int)this->position.x, (int)this->position.y);

	//update the animation state
	if (this->shellForm && frame % 7 == 0) this->shellTextureLoop->NextFrame();
	else if (frame % 17 == 0) this->textureLoop->NextFrame();

	

	//update hitbox position
	//this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 100 };
	this->hitbox.x = this->position.x - (50 / 2);
	this->hitbox.y = this->position.y - (100 / 2);


	//update texture proteries based on new position
	this->textureLoop->Update();
	this->shellTextureLoop->Update();
}

void RedKoopaEnemy::Draw()
{
	if (!this->shellForm) this->textureLoop->Draw();
	else this->shellTextureLoop->Draw();
	
	//DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, 0, WHITE);
	if (this->health < this->maxHealth) this->DrawHealthbar(50, 1.0f);


	//Enemy::Draw(); // draw hitbox
}