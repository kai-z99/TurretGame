#include "SlimeEnemy.h"

#include "TextureLoop.h"
#include "textures.h"

SlimeEnemy::SlimeEnemy(bool small)
{
	this->small = small;
	

	this->id = 6;

	if (!this->small) //big slime
	{
		this->splitted = false;
		this->damage = 10;
		this->maxHealth = 350.0f;
		this->health = this->maxHealth;
		this->coinDropAmount = 50;

		this->knockbackMultiplier = 0.5f;

		this->baseVelocity = { -1.5,0.0f };
		this->currentVelocity = this->baseVelocity;

		this->hitbox = { this->position.x - (75 / 2), this->position.y - (75 / 2), 75, 75 };
		this->textureLoop = new TextureLoop(&textures[25], 4, 3.0f, this->position);
	}

	else //mini slime
	{
		this->splitted = true;
		this->damage = 3;
		this->maxHealth = 80.0f;
		this->health = this->maxHealth;
		this->coinDropAmount = 14;

		this->knockbackMultiplier = 1.3f;

		this->baseVelocity = { -2.0,0.0f };
		this->currentVelocity = this->baseVelocity;

		this->hitbox = { this->position.x - (37.5f / 2), this->position.y - (37.5f / 2), 37.5f, 37.5f };
		this->textureLoop = new TextureLoop(&textures[25], 4, 1.5f, this->position);
	}

}

void SlimeEnemy::Update(unsigned int frame)
{
	// update position and velocity and check if death
	Enemy::Update(frame);



	//update position of texture
	this->textureLoop->SetPosition((int)this->position.x, (int)this->position.y);

	//update the animation state
	if (frame % 6 == 0) this->textureLoop->NextFrame();

	//update hitbox position
	//this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 100 };
	if (!this->small)
	{
		this->hitbox.x = this->position.x - (75 / 2.0f);
		this->hitbox.y = this->position.y - (75 / 2.0f);
	}

	else
	{
		this->hitbox.x = this->position.x - (37.5f / 2);
		this->hitbox.y = this->position.y - (37.5f / 2);
	}
	
	//update texture proteries based on new position
	this->textureLoop->Update();
}

void SlimeEnemy::Draw()
{
	//DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, 0, WHITE);
	this->textureLoop->Draw();
	if (this->health < this->maxHealth) this->DrawHealthbar(50, 1.0f);

	//Enemy::Draw(); // draw hitbox
}
