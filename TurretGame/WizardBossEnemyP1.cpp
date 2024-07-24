#include "WizardBossEnemyP1.h"

#include <iostream>

#include "TextureLoop.h"
#include "textures.h"

#include "constants.h"
#include "helpers.h"

WizardBossEnemyP1::WizardBossEnemyP1()
{
	this->id = 11;
	this->damage = 100;
	this->maxHealth = 50000.0f; //15000
	this->health = this->maxHealth;
	this->coinDropAmount = GetRandomValue(2502, 2550);

	this->knockbackMultiplier = 0.01f;
	this->resistChill = true;
	this->speed = 3.0f;

	this->baseVelocity = { -this->speed,0.0f };
	this->crossVelocity = { this->speed, this->speed };
	this->fallVelocity = { 0.0f, this->speed * 2.0f };
	this->ascendVelocity = {0.0f, -this->speed};
	this->currentVelocity = this->baseVelocity;

	this->hitbox = { this->position.x - (200 / 2), this->position.y - (350 / 2), 200, 350 };
	this->textureLoop = new TextureLoop(&textures[47], 8, 4.0f, this->position);
	this->p2Texture = new TextureLoop(&textures[50], 8, 4.0f, this->position);
	this->textureLoop->ToggleMirrorImage();
	this->p2Texture->ToggleMirrorImage();

	this->localFramecount = 0;
	this->modeFramecount = 0;
	this->isShootFrame = false;
	this->isBurstFrame = false;
	this->phase = 1;
	this->mode = 1;
	this->timesCrossed = 0;

	this->fireWithBullet = true;

}

void WizardBossEnemyP1::Update(unsigned int frame)
{
	this->localFramecount++;
	this->modeFramecount++;
	Enemy::Update(frame);

	this->HandlePhaseSwitching();
	this->HandleModeSwitching();
	this->HandleMovement();
	this->HandleShooting();

	//update textureLoop
	this->textureLoop->SetPosition((int)this->position.x, (int)this->position.y);
	this->p2Texture->SetPosition((int)this->position.x, (int)this->position.y);

	if (frame % 6 == 0) this->textureLoop->NextFrame();
	if (frame % 6 == 0) this->p2Texture->NextFrame();

	this->textureLoop->Update();
	this->p2Texture->Update();

	this->hitbox.x = this->position.x - (200 / 2.0f);
	this->hitbox.y = this->position.y - (350 / 2.0f);
}

void WizardBossEnemyP1::HandlePhaseSwitching()
{
	//half health
	if (this->health < (this->maxHealth / 2.0f) && this->phase == 1)
	{
		this->phase = 2;
		this->speed = 4.5f;
		this->baseVelocity = { -this->speed,0.0f };
		this->crossVelocity = { this->speed, this->speed };
		this->fallVelocity = { 0.0f, this->speed * 2.0f };
		this->ascendVelocity = { 0.0f, -this->speed };
	}
}

void WizardBossEnemyP1::HandleModeSwitching()
{
	switch (this->mode)
	{
	case 1:
		if (this->timesCrossed == 4)
		{
			this->mode = 2;
			this->timesCrossed = 0;
			this->modeFramecount = 0;
		}
		break;

	case 2:
		if (this->timesCrossed == 1)
		{
			this->mode = 3;
			this->timesCrossed = 0;
			this->modeFramecount = 0;
		}
		break;

	case 3:
		if (fabs(this->position.x - this->basePosition.x) < 8.0f && fabs(this->position.y - this->basePosition.y) < 8.0f)
		{
			//if phase 1, go back to mode 1. if 2, go ahead to phase 4
			this->phase == 1 ? this->mode = 1 : this->mode = 4;
			this->modeFramecount = 0;
		}
		break;

	case 4:
		if (this->modeFramecount > 200)
		{
			this->mode = 5;
			this->modeFramecount = 0;
		}
		break;

	case 5:
		if (this->timesCrossed >= 6)
		{
			this->mode = 1;
			this->timesCrossed = 0;
			this->modeFramecount = 0;
		}
		break;

	}
}

void WizardBossEnemyP1::HandleMovement()
{
	switch (this->mode)
	{
	//cross
	case 1:
		if (this->modeFramecount <= 1) this->currentVelocity = this->crossVelocity;

		//go to top right if hits bottom right
		if (this->position.y > screenHeight + 200 && this->currentVelocity.x > 0)
		{
			this->position = { (float)screenWidth, -200.0f };
			this->currentVelocity.x = -this->currentVelocity.x;

			//update to new cross speed if phase switched to 2
			if (this->phase == 2)
			{
				this->currentVelocity.x = -this->crossVelocity.x;
				this->currentVelocity.y = this->crossVelocity.y;
			}
			this->timesCrossed++;
		}

		//go to top left if hits bottom left
		else if (this->position.y > screenHeight + 200 && this->currentVelocity.x < 0)
		{
			this->position = { (float)deathBoundaryX + 150, -200.0f };
			this->currentVelocity.x = -this->currentVelocity.x;

			//update to new cross speed if phase switched to 2
			if (this->phase == 2)
			{
				this->currentVelocity.x = this->crossVelocity.x;
				this->currentVelocity.y = this->crossVelocity.y;
			}

			this->timesCrossed++;
		}	
		break;
	
	//drop
	case 2:
	{
		float xModifier = 3.0f * sinf(this->modeFramecount * 0.1f);

		if (this->modeFramecount <= 1)
		{
			//start position of falling move
			this->position = this->fallStartPosition;
			this->currentVelocity = this->fallVelocity;
		}

		this->position.x += xModifier;

		//when its at the bttom of the screen
		if (this->position.y > screenHeight + 200)
		{
			//if itst too close, move it back
			if (this->position.x - 300.0f < deathBoundaryX + 50.0f)
			{
				this->timesCrossed++;
				this->position = this->fallStartPosition;
			}

			//else move it fwd
			else
			{
				this->position.x -= 300.0f;
				this->position.y = this->fallStartPosition.y;
			}

			//get new fall speed in phase 2
			if (this->phase == 2)
			{
				this->currentVelocity.y = this->fallVelocity.y;
			}

		}
	}
		break;

	//reposition
	case 3:
		//x axis reposition
		if (this->position.x < this->basePosition.x - 4.0f)
		{
			this->currentVelocity.x = this->speed;
		}
		else if (this->position.x > this->basePosition.x + 4.0f)
		{
			this->currentVelocity.x = -this->speed;
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
	
	//center
	case 4:
		//hovering
		this->currentVelocity.y = 0.8f * sinf((float)this->modeFramecount * 0.04f);
		this->currentVelocity.x = 0.0f;
		break;

	//infinite ascend
	case 5:
		float acceleration = 0.1f;
		this->currentVelocity.x = 0;

		if (this->modeFramecount <= 1) this->currentVelocity.y = this->ascendVelocity.y;
		else this->currentVelocity.y -= acceleration;

		if (this->position.y < menuBoundaryY - 200.0f)
		{
			this->position.y = screenHeight + 215.0f;
			this->timesCrossed++;
		}
	}


}

void WizardBossEnemyP1::HandleShooting()
{
	// in bounds
	if (this->position.y > menuBoundaryY + 100 && this->position.y < screenHeight - 100)
	{
		//phase 1
		if (this->phase == 1)
		{
			this->isBurstFrame = false;
			int rand = GetRandomValue(1, 4);

			// 75% chance every 60 frames, always shoots if in dropping mode
			if (this->localFramecount % 60 == 0 && (rand != 1 || this->mode == 2))
			{
				this->isShootFrame = true;
			}
			else
			{
				this->isShootFrame = false;
			}
		}

		//phase 2
		else
		{
			int rand = GetRandomValue(1, 100);
			
			//cross and reposition: slower shooting with chance of burst
			if (this->mode == 1 || this->mode == 3)
			{
				//30 percent chance of burst
				if (this->localFramecount % 50 == 0 && rand > 70)
				{
					this->isBurstFrame = true;
					this->isShootFrame = false;
				}

				//high chance of normal shot
				else if (this->localFramecount % 50 == 0 && rand > 15) //85% chance every 50 frames
				{
					this->isShootFrame = true;
					this->isBurstFrame = false;
					this->fireWithBullet = !this->fireWithBullet;
				}

				else
				{
					this->isShootFrame = false;
					this->isBurstFrame = false;
				}
			}

			//ascending/drop: shoot frequently. never burst.
			else if (this->mode == 5 || this->mode == 2)
			{
				this->isBurstFrame = false;

				if (this->localFramecount % 30 == 0)
				{
					this->isShootFrame = true;
					this->fireWithBullet = !this->fireWithBullet;
				}

				else
				{
					this->isShootFrame = false;
				}
				
			}

			//hover: always shoot burst at modeframe 60
			else if (this->mode == 4)
			{
				this->isShootFrame = false;

				if (this->modeFramecount == 60)
				{
					this->isBurstFrame = true;
				}
				else
				{
					this->isBurstFrame = false;
				}
				
			}
		}	
	}

	//no shooting out of bounds
	else
	{
		this->isShootFrame = false;
		this->isBurstFrame = false;
	}
	
}


void WizardBossEnemyP1::Draw()
{
	if (this->phase == 1)
	{
		this->textureLoop->Draw();
		this->DrawBossHealthbar("BROKEN SAND WIZARD", GREEN, RED);
	}
	else
	{
		this->p2Texture->Draw();
		this->DrawBossHealthbar("THE DUNE FLAME", BLUE, DARKPURPLE);
	}
		

	//Enemy::Draw(); // draw hitbox
}

int WizardBossEnemyP1::GetPhase() const
{
	return this->phase;
}

std::pair<Vector2, Vector2> WizardBossEnemyP1::GetBulletSpawnInstructions()
{
	Vector2 pos;
	Vector2 vel;
	float angle = GetRandomFloat(-PI / 4.0f, PI / 4.0f);
	float speed = GetRandomFloat(2.0f,3.5f);
	int roll1 = GetRandomValue(-2, 2);
	int roll2 = GetRandomValue(-2, 2);
	// cos(angle) = x/speed
	// speed * cos(angle) = x
	

	switch (this->mode)
	{
	//cross
	case 1:
		//pos
		pos = { this->position.x + roll1 * 40.0f, this->position.y + roll2 * 40.0f };
		//make sure its not too far down/up
		if (pos.y > screenHeight - 50) this->position.y = screenHeight - 60;
		else if (pos.y < menuBoundaryY + 50) this->position.y = menuBoundaryY + 60;

		//vel
		vel = { -speed * cosf(angle), speed * sinf(angle) };

		break;

	//drop
	case 2:
		//pos
		pos = { this->position.x + 100.0f, this->position.y };
		//make sure its not too far down/up
		if (pos.y > screenHeight - 50) this->position.y = screenHeight - 60;
		else if (pos.y < menuBoundaryY + 50) this->position.y = menuBoundaryY + 60;

		//vel
		vel = { -speed * cosf(angle), speed * sinf(angle) };
		break;

	//reposition
	case 3:
		//pos
		pos = { this->position.x + roll1 * 40.0f, this->position.y + roll2 * 40.0f };
		//make sure its not too far down/up
		if (pos.y > screenHeight - 50) this->position.y = screenHeight - 60;
		else if (pos.y < menuBoundaryY + 50) this->position.y = menuBoundaryY + 60;


		//vel
		vel = { -speed * cosf(angle), speed * sinf(angle) };
		break;

	//center
	case 4:
		//no random spawns in this phase.
		std::cout << "Warning: no random spawns in this mode.\n";
		break;
	
	//ascend
	case 5:
		//pos
		pos = { this->position.x + 100.0f, this->position.y };
		//make sure its not too far down/up
		if (pos.y > screenHeight - 50) this->position.y = screenHeight - 60;
		else if (pos.y < menuBoundaryY + 50) this->position.y = menuBoundaryY + 60;

		//vel
		vel = { -speed * cosf(angle), speed * sinf(angle) };
		break;

	default:
		std::cout << "Warning: no spawn info for this mode.\n";
		break;
	}

	return { pos,vel };
}

