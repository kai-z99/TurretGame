#include "BalloonBossEnemy.h"

#include "textures.h"
#include "TextureLoop.h"


BalloonBossEnemy::BalloonBossEnemy()
{
	this->id = 7;
	this->damage = 100;
	this->maxHealth = 15000.0f;
	this->health = this->maxHealth;
	this->coinDropAmount = GetRandomValue(2502, 2550);

	this->knockbackMultiplier = 0.01f;
	this->resistChill = true;
	this->speed = 3.0f;

	this->baseVelocity = { -this->speed,0.0f };
	this->ascendVelocity = {0.0f, -this->speed };
	this->retreatVelocity = { this->speed, 0.0f };

	this->currentVelocity = this->baseVelocity;

	this->hitbox = { this->position.x - (200 / 2), this->position.y - (350 / 2), 200, 350 };
	this->textureLoop = new TextureLoop(&textures[31], 2, 8.0f, this->position);
	this->shootLoop = new TextureLoop(&textures[33], 7, 8.0f, this->position);

	this->mode = 0;
	this->phase = 1;
	this->isShootFrame = false;
	this->spawnedShield = false;

	this->rotateFrameCount = 0;
	this->localFrameCount = 0;
	this->readyShootFrames = 0;
	this->cyclesComplete = 0;
}

void BalloonBossEnemy::Update(unsigned int frame)
{
	this->localFrameCount++;

	if (this->readyShootFrames > 0) this->readyShootFrames--;

	// update position and velocity and check if death
	Enemy::Update(frame);

	if (this->health < (this->maxHealth / 2.0f) && this->phase == 1)
	{
		this->phase = 2;
	}

	if (this->health < (this->maxHealth / 3.0f) && this->mode != 2 && this->phase == 2) //dont disrupt the circle cycle, can disruot the up and down since he repositions after
	{
		this->phase = 3;
	}


	if (phase == 3)
	{
		this->speed = 5.0f;
		this->baseVelocity = { -this->speed,0.0f };
		this->ascendVelocity = { 0.0f, -this->speed };
		this->retreatVelocity = { this->speed, 0.0f };
		this->tint = ORANGE;
		this->shootLoop->SetTint(ORANGE);
	}

	this->HandleModeSwitching();
	this->HandleMovement();
	this->HandleShooting();

	//update postion of texture
	this->textureLoop->SetPosition((int)this->position.x, (int)this->position.y);
	this->shootLoop->SetPosition((int)this->position.x, (int)this->position.y);

	//update the animation state
	if (frame % 20 == 0) this->textureLoop->NextFrame();

	//if its getting ready to shoot advance the shoot animation
	if (this->readyShootFrames > 0)
	{
		if (frame % 9 == 0)
		{
			this->shootLoop->NextFrame();
		}
	}

	else //if its not curerntly shooting then set its animation back to the first frame
	{
		this->shootLoop->SetAnimationState(1);
	}

	
	//update hitbox position
	//this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 100 };
	this->hitbox.x = this->position.x - (200.0f / 2);
	this->hitbox.y = this->position.y - (350.0f / 2);

	//update texture proteries based on new position
	this->textureLoop->Update();
	this->shootLoop->Update();
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
		//x axis reposition
		if (this->position.x < this->basePosition.x)
		{
			this->currentVelocity.x = this->speed;
		}
		else
		{
			this->currentVelocity.x = 0;
		}

		//y axis reposition
		if (this->position.y < this->basePosition.y - 4.0f)
		{
			this->currentVelocity.y = this->speed;
		}
		else if (this->position.y > this->basePosition.y + 4.0f)
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
void BalloonBossEnemy::HandleModeSwitching()
{
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

		// 4PI = 0.012f / 3 * speed * framecount. find framecount for 2 rotations (4PI)
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

		// 4PI = 0.012f / 3 * speed * framecount. 
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

}
void BalloonBossEnemy::HandleShooting()
{
	int rand1 = GetRandomValue(1, 2);
	int rand2 = GetRandomValue(1, 3);

	switch (this->phase)
	{
	case 1:
		// 1/3 chance to shoot
		if (this->localFrameCount % 57 == 0)
		{
			if (rand1 == 1 || this->mode == 4) this->readyShootFrames = 56; // 7 sections anim, 8 frames per section FOR A TOTLA OF 56 frames
		}
		break;

	case 2:
		// 2/3 chance to shoot
		if (this->localFrameCount % 57 == 0)
		{
			if (rand2 == 1 || rand2 == 2 || this->mode == 4) this->readyShootFrames = 56; 
		}
		break;

	case 3:
		//  
		if (this->localFrameCount % 57 == 0)
		{
			if (rand1 == 1 || rand2 == 2 || rand2 == 3 || this->mode == 4) this->readyShootFrames = 56;
		}
		break;

	}
	
	if (this->readyShootFrames == 16) this->isShootFrame = true; //16 is the frame where the bullet is release in the animation
	else this->isShootFrame = false;
}
void BalloonBossEnemy::Draw()
{
	//show the thrwoing aniumation if getting ready to shoot
	if (this->readyShootFrames > 0) this->shootLoop->Draw();

	//else show the idle animation
	else this->textureLoop->Draw();
	
	this->DrawBossHealthbar("ANGRY BALLOON BOY");

	//Enemy::Draw(); // draw hitbox
}

int BalloonBossEnemy::GetPhase() const
{
	return this->phase;
}


