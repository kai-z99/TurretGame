#include "BalloonBossEnemy.h"

#include "textures.h"
#include "TextureLoop.h"


BalloonBossEnemy::BalloonBossEnemy()
{
	this->id = 7;
	this->damage = 100;
	this->maxHealth = 15000.0f;
	this->health = this->maxHealth;
	this->coinDropAmount = GetRandomValue(502, 550);

	this->knockbackMultiplier = 0.01f;

	this->speed = 3.0f;

	this->baseVelocity = { -this->speed,0.0f };
	this->ascendVelocity = {0.0f, -this->speed };
	this->retreatVelocity = { this->speed, 0.0f };

	this->currentVelocity = this->baseVelocity;

	this->hitbox = { this->position.x - (200 / 2), this->position.y - (350 / 2), 200, 350 };
	this->textureLoop = new TextureLoop(&textures[31], 2, 8.0f, this->position);

	this->mode = 0;

	this->rotateFrameCount = 0;
	this->localFrameCount = 0;
	this->cyclesComplete = 0;
}

void BalloonBossEnemy::Update(unsigned int frame)
{
	this->localFrameCount++;

	if (this->health < (this->maxHealth / 3))
	{
		this->speed = 5.0f;
		this->baseVelocity = { -this->speed,0.0f };
		this->ascendVelocity = { 0.0f, -this->speed };
		this->retreatVelocity = { this->speed, 0.0f };
	}


	//while going forward 
	if (this->mode == 0)
	{
		//if reach middle,
		if (this->position.x < (screenWidth / 2.0f))
		{
			//ascend up if less than 4 cycles complete
			if (this->cyclesComplete <= 2)
			{
				this->mode = 1;
			}

			//continue forward for the kill if not
			else
			{
				this->mode = 0;
			}			
		}
	}

	//ascend
	else if (this->mode == 1)
	{
		if (this->position.y < 350)
		{
			this->mode = 2;
		}
	}


	//rotate twice
	else if (this->mode == 2)
	{
		this->rotateFrameCount++;

		if (this->rotateFrameCount > (2 * 2 * PI) / (0.012f / 3 * this->speed))
		{
			this->mode = 3;
			this->rotateFrameCount = 0;
		}
	}
	
	//retreat
	else if (this->mode == 3)
	{
		if (this->position.x > 1700)
		{
			this->mode = 4;
		}
	}

	//up and down 2 cycles
	else if (this->mode == 4)
	{
		this->rotateFrameCount++;

		if (this->rotateFrameCount > (2 * 2 * PI) / (0.02f / 3 * this->speed))
		{
			this->mode = 5;
			this->rotateFrameCount = 0;
		}
	}

	//repostion to original position
	if (this->mode == 5)
	{
		if (fabs(this->position.x - this->basePosition.x) < 8.0f && fabs(this->position.y - this->basePosition.y) < 8.0f)
		{
			this->mode = 0;
			this->cyclesComplete++;
		}
	}

	this->HandleMovement();

	// update position and velocity and check if death
	Enemy::Update(frame);

	//update postion of texture
	this->textureLoop->SetPosition((int)this->position.x, (int)this->position.y);

	//update the animation state
	if (frame % 20 == 0) this->textureLoop->NextFrame();

	//update hitbox position
	//this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 100 };
	this->hitbox.x = this->position.x - (200.0f / 2);
	this->hitbox.y = this->position.y - (350.0f / 2);

	//update texture proteries based on new position
	this->textureLoop->Update();


}

void BalloonBossEnemy::HandleMovement()
{

	switch (this->mode)
	{
		//forward
	case 0:
		this->currentVelocity.x = this->baseVelocity.x;
		this->currentVelocity.y = 0.8f * sinf(this->localFrameCount * 0.04f);
		break;

		//ascend
	case 1:
		this->currentVelocity = this->ascendVelocity;
		break;

		//circle
	case 2:
		this->currentVelocity.y = 3 / 3.0f * this->speed * sinf(this->rotateFrameCount * 0.012f / 3 * this->speed);
		this->currentVelocity.x = 3 / 3.0f * this->speed * cosf(this->rotateFrameCount * 0.012f / 3 * this->speed);
		break;

		//retreat
	case 3:
		this->currentVelocity = this->retreatVelocity;
		this->currentVelocity.y = 0.8f * sinf(this->localFrameCount * 0.04f);
		break;

		//wave
	case 4:
		this->currentVelocity.x = 0;
		this->currentVelocity.y = 5.0f / 3.0f * this->speed * sinf(this->rotateFrameCount * 0.02f / 3 * this->speed);
		break;

		//re-position
	case 5:
		if (this->position.x < this->basePosition.x)
		{
			this->currentVelocity.x = this->speed;
		}
		else if (this->position.x > this->basePosition.x)
		{
			this->currentVelocity.x = -this->speed;
		}
		else
		{
			this->currentVelocity.x = 0;
		}

		if (this->position.y < this->basePosition.y)
		{
			this->currentVelocity.y = this->speed;
		}
		else if (this->position.y > this->basePosition.y)
		{
			this->currentVelocity.y = -this->speed;
		}
		else
		{
			this->currentVelocity.y = 0;
		}
		break;
	}
}
void BalloonBossEnemy::Draw()
{
	this->textureLoop->Draw();
	this->DrawBossHealthbar("ANGRY BALLOON BOY");

	//Enemy::Draw(); // draw hitbox
}


