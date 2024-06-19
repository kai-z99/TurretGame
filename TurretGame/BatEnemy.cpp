#include "BatEnemy.h"
#include "textures.h"
#include "TextureLoop.h"

BatEnemy::BatEnemy()
{
	this->id = 5;
	this->damage = 3;
	this->maxHealth = 5;
	this->health = this->maxHealth;
	this->coinDropAmount = GetRandomValue(8, 18);

	this->knockbackMultiplier = 1.5f;

	this->baseVelocity = { -2.0f, 0.0f };

	this->currentVelocity = this->baseVelocity;
	this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 50 }; //50 and 100 are the hitbox dimensions... minus half for centering purpose
	this->textureLoop = new TextureLoop(&textures[8], 4, 3.0f, this->position);

	this->localFrameCount = 0;
}

void BatEnemy::Update(unsigned int frame)
{
	this->localFrameCount++;

	// update position and velocity and check if death
	Enemy::Update(frame);

	this->currentVelocity.y = 3 * sin(this->localFrameCount * 0.03);

	//update postion of texture
	this->textureLoop->SetPosition(this->position.x, this->position.y);

	//update the animation state
	if (frame % 10 == 0) this->textureLoop->NextFrame();

	//update hitbox position
	//this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 100 };
	this->hitbox.x = this->position.x - (50 / 2);
	this->hitbox.y = this->position.y - (50 / 2);


	//update texture proteries based on new position
	this->textureLoop->Update();

}

void BatEnemy::Draw()
{
	this->textureLoop->Draw();
	if (this->health < this->maxHealth) this->DrawHealthbar(50, 1.0f);

	//Enemy::Draw(); // draw hitbox
}