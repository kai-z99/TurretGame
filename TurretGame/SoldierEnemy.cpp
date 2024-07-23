#include "SoldierEnemy.h"
#include "textures.h"
#include "TextureLoop.h"

SoldierEnemy::SoldierEnemy()
{
	this->id = 1;
	this->damage = 5;
	this->maxHealth = 100.0f;
	this->health = this->maxHealth;
	this->coinDropAmount = 30;

	this->knockbackMultiplier = 1.0f;

	this->baseVelocity = { -3.0f,0.0f };
	this->currentVelocity = this->baseVelocity;

	this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 100}; //50 and100 are the hitbox dimensions... minus half for centering purpose
	this->textureLoop = new TextureLoop(&textures[0], 6, 1.0f, this->position);
	this->textureLoop->ToggleMirrorImage();
}

void SoldierEnemy::Update(unsigned int frame)
{
	// update position and velocity and check if death
	Enemy::Update(frame);

	//update position of texture
	this->textureLoop->SetPosition((int)this->position.x, (int)this->position.y);

	//update the animation state
	if (frame % 6 == 0) this->textureLoop->NextFrame();

	//update hitbox position
	//this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 100 };
	this->hitbox.x = this->position.x - (50 / 2);
	this->hitbox.y = this->position.y - (100 / 2);

	//update texture proteries based on new position
	this->textureLoop->Update();
	
}

void SoldierEnemy::Draw()
{
	//DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, 0, WHITE);
	this->DrawShadow(0,0,1.0f);
	this->textureLoop->Draw();
	if (this->health < this->maxHealth) this->DrawHealthbar(50, 1.0f);



	//Enemy::Draw(); // draw hitbox
}
