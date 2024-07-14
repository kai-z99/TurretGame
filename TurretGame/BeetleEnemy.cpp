#include "BeetleEnemy.h"

#include "textures.h"
#include "TextureLoop.h"

#include "constants.h"

BeetleEnemy::BeetleEnemy()
{
	this->id = 9;
	this->damage = 10;
	this->maxHealth = 1000.0f;
	this->health = this->maxHealth;
	this->coinDropAmount = GetRandomValue(142, 148);

	this->localFramecount = 0;
	this->timesSwitched = 0;

	this->knockbackMultiplier = 0.2f;
	this->baseVelocity = { -1.5,0.0f };
	this->currentVelocity = this->baseVelocity;
	this->hitbox = { this->position.x - (100 / 2), this->position.y - (80 / 2), 100, 80 };
	this->textureLoop = new TextureLoop(&textures[38], 3, 4.0f, this->position);
	this->upLoop = new TextureLoop(&textures[39], 3, 4.0f, this->position); //starts facing down
	  
	//upLoop->ToggleReflectedImage();
}

void BeetleEnemy::Update(unsigned int frame)
{
	this->localFramecount++;
	// update position and velocity and check if death
	Enemy::Update(frame);

	this->HandleDirectionSwitch();
	

	//update postion of texture
	this->textureLoop->SetPosition((int)this->position.x, (int)this->position.y);
	this->upLoop->SetPosition((int)this->position.x, (int)this->position.y);

	//update the animation state
	if (frame % 10 == 0)
	{
		this->textureLoop->NextFrame();
		this->upLoop->NextFrame();
	}

	//update hitbox position
	//this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 100 };
	this->hitbox.x = this->position.x - (100 / 2.0f);
	this->hitbox.y = this->position.y - (80 / 2.0f);

	//update texture proteries based on new position
	this->textureLoop->Update();
	this->upLoop->Update();
	this->upLoop->SetTint(this->tint);
}

void BeetleEnemy::Draw()
{
	//moving fwd
	if (this->currentVelocity.x < 0.0f) this->textureLoop->Draw();

	//moving vertical
	else this->upLoop->Draw();
	//DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, 0, WHITE);
	if (this->health < this->maxHealth) this->DrawHealthbar(50, 1.0f);

	//Enemy::Draw(); // draw hitbox
}

void BeetleEnemy::HandleDirectionSwitch()
{
	//switch walking direction 1/3 chance each second
	if (this->localFramecount % 60 == 0 && GetRandomValue(1,3) == 1)
	{
		//if its moving forward
		if (this->currentVelocity.x < 0.0f)
		{
			//bottom half of screen, move up.
			if (this->position.y >= halfwayLevelY)
			{
				this->currentVelocity.x = 0.0f;
				this->currentVelocity.y = -1.5f;

				//make sure the texture is facing up.
				if (!this->isFacingUp())
				{
					this->upLoop->ToggleReflectedImage();
					this->timesSwitched++;
				}
			}

			//top half, go down
			else
			{
				this->currentVelocity.x = 0.0f;
				this->currentVelocity.y = 1.5f;

				//if texture is facing up, turn it to face down.
				if (this->isFacingUp())
				{
					this->upLoop->ToggleReflectedImage();
					this->timesSwitched++;
				}
			}


		}

		//if its moving vertically
		else
		{
			this->currentVelocity.y = 0.0f;
			this->currentVelocity.x = this->baseVelocity.x;
		}
	}

	//if too low, make it go up.
	if (this->position.y > screenHeight - 80)
	{
		this->currentVelocity.x = 0.0f;
		this->currentVelocity.y = -1.5f;

		if (!this->isFacingUp())
		{
			this->upLoop->ToggleReflectedImage();
			this->timesSwitched++;
		}
	}

	//if its too high, make it go down
	else if (this->position.y < menuBoundaryY + 80)
	{
		this->currentVelocity.x = 0.0f;
		this->currentVelocity.y = 1.5f;

		if (this->isFacingUp())
		{
			this->upLoop->ToggleReflectedImage();
			this->timesSwitched++;
		}
	}
	

}

bool BeetleEnemy::isFacingUp() const
{
	return this->timesSwitched % 2 != 0;
}
