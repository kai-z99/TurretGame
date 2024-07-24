#include "WizardBulletEnemy.h"

#include "TextureLoop.h"
#include "textures.h"

#include "constants.h"

WizardBulletEnemy::WizardBulletEnemy()
{
	this->id = 12;
	this->damage = 10;
	this->maxHealth = 410.0f;
	this->health = this->maxHealth;
	this->coinDropAmount = GetRandomValue(1, 2);

	this->knockbackMultiplier = 0.0f;
	this->baseVelocity = { 0.0f,0.0f }; //base case, should not appear. should set base vecloty using wizard boss calculations
	this->currentVelocity = this->baseVelocity;
	this->hitbox = { this->position.x - (54 / 2), this->position.y - (54 / 2), 54, 54 };
	this->textureLoop = new TextureLoop(&textures[48], 5, 8.1f, this->position);
	this->startLoop = new TextureLoop(&textures[49], 5, 8.1f, this->position);

	this->flippedFrame = -210; //to prevent rapid flipping
	this->ignited = false;
}

void WizardBulletEnemy::Update(unsigned int frame)
{
	if (this->ignited)
	{
		this->tint = SKYBLUE;
	}
	else
	{
		this->tint = WHITE;
	}

	this->localFramecount++;
	//bullet rests for one second
	if (this->localFramecount < 60)
	{
		this->currentVelocity = { 0,0 };
	}

	//speed up bullet until its at the base velocity
	else
	{
		//non ignited behavior
		if (!this->ignited)
		{
			float acceleration = 0.07f;

			if (this->currentVelocity.x < this->baseVelocity.x)
			{
				this->currentVelocity.x += acceleration;
			}
			else if (this->currentVelocity.x > this->baseVelocity.x)
			{
				this->currentVelocity.x -= acceleration;
			}

			if (this->currentVelocity.y < this->baseVelocity.y)
			{
				this->currentVelocity.y += acceleration;
			}
			else if (this->currentVelocity.y > this->baseVelocity.y)
			{
				this->currentVelocity.y -= acceleration;
			}
		}

		//ignited behavior
		else
		{
			float acceleration = 0.07f;

			this->currentVelocity.y = 0.0f;
			this->currentVelocity.x -= acceleration;
		}
		

	}

	//cant rapidly flip
	if (this->localFramecount - this->flippedFrame > 210 && (this->position.y > screenHeight - 50 || this->position.y < menuBoundaryY + 50))
	{
		this->baseVelocity.y = -this->baseVelocity.y;
		this->flippedFrame = localFramecount;
	}

	// update position and velocity and check if death
	Enemy::Update(frame);

	//update postion of texture
	this->textureLoop->SetPosition((int)this->position.x, (int)this->position.y);
	this->startLoop->SetPosition((int)this->position.x, (int)this->position.y);

	//update the animation state
	if (frame % 6 == 0)
	{
		this->textureLoop->NextFrame();
		this->startLoop->NextFrame();
	}

	//update hitbox position
	//this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 100 };
	this->hitbox.x = this->position.x - (54 / 2.0f);
	this->hitbox.y = this->position.y - (54 / 2.0f);

	//update texture proteries based on new position
	this->textureLoop->Update();
	this->startLoop->Update();
}

void WizardBulletEnemy::Draw()
{
	//ready up animation
	if (this->localFramecount < 60)
	{
		this->startLoop->Draw();
	}
	else
	{
		this->textureLoop->Draw();
	}
	
	//Enemy::Draw(); //hitbox
}
