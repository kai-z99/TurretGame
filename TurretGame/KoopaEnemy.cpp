#include "KoopaEnemy.h"
#include "textures.h"
#include "TextureLoop.h"

KoopaEnemy::KoopaEnemy()
{
	this->id = 2;
	this->damage = 3;
	this->maxHealth = 400.0f;
	this->health = this->maxHealth;
	this->coinDropAmount = GetRandomValue(12,18);

	this->knockbackMultiplier = 0.5f;
	this->baseVelocity = { -1.5,0.0f };
	this->currentVelocity = this->baseVelocity;
	this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 100 }; //50 and 100 are the hitbox dimensions... minus half for centering purpose
	this->textureLoop = new TextureLoop(&textures[3], 2, 4.0f, this->position);
}

void KoopaEnemy::Update(unsigned int frame)
{
	// update position and velocity and check if death
	Enemy::Update(frame); 

	//update postion of texture
	this->textureLoop->SetPosition((int)this->position.x, (int)this->position.y);

	//update the animation state
	if (frame % 20 == 0) this->textureLoop->NextFrame(); 

	//update hitbox position
	//this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 100 };
	this->hitbox.x = this->position.x - (50 / 2.0f);
	this->hitbox.y = this->position.y - (100 / 2.0f);

	//update texture proteries based on new position
	this->textureLoop->Update();
	
}

void KoopaEnemy::Draw()
{
	this->textureLoop->Draw();
	//DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, 0, WHITE);
	if (this->health < this->maxHealth) this->DrawHealthbar(50, 1.0f);
	

	//Enemy::Draw(); // draw hitbox
}