#include "WizardFireEnemy.h"

#include "TextureLoop.h"
#include "textures.h"


#include "constants.h"
#include "helpers.h"

WizardFireEnemy::WizardFireEnemy()
{
	this->id = 13;
	this->damage = 20;
	this->maxHealth = 1033.3f;
	this->health = this->maxHealth;
	this->coinDropAmount = GetRandomValue(1, 2);

	this->knockbackMultiplier = 0.1f;
	this->baseVelocity = { 0.0f,GetRandomFloat(-4.5f, -7.5f)};
	this->currentVelocity = this->baseVelocity;
	this->hitbox = { this->position.x - (112 / 2), this->position.y - (150 / 2), 112, 150 };
	this->textureLoop = new TextureLoop(&textures[51], 4, 6.0f, this->position);

	this->hoverMode = false;
	this->stopPointY = GetRandomValue(menuBoundaryY + 150, screenHeight - 150); //where the fire starts to stop
	this->localFramecount = 0;

	this->resistChill = true;
}

void WizardFireEnemy::Update(unsigned int frame)
{
	this->localFramecount++;
	// update position and velocity and check if death
	Enemy::Update(frame);

	if (this->hoverMode)
	{
		this->currentVelocity.y = 0.8f * sinf((float)this->localFramecount * 0.04f);
	}

	else
	{
		//stop floating up when reach stop point
		if (this->position.y < stopPointY && this->currentVelocity.y != 0.0f)
		{
			this->currentVelocity.y = this->currentVelocity.y * 0.95f;
			float acceleration = 0.01f;
			this->currentVelocity.y += acceleration;

			if (this->currentVelocity.y > 0.0f) this->currentVelocity.y = 0.0f;
		}
		else if (this->currentVelocity.y == 0.0f)
		{
			this->hoverMode = true;
		}
	}
	


	//update postion of texture
	this->textureLoop->SetPosition((int)this->position.x, (int)this->position.y);

	//update the animation state
	if (frame % 8 == 0) this->textureLoop->NextFrame();

	//update hitbox position
	//this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 100 };
	this->hitbox.x = this->position.x - (112 / 2.0f);
	this->hitbox.y = this->position.y - (150 / 2.0f);

	//update texture proteries based on new position
	this->textureLoop->Update();
}

void WizardFireEnemy::Draw()
{
	this->DrawShadow(-8, 0, 0.7f);
	this->textureLoop->Draw();
	//DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, 0, WHITE);
	//if (this->health < this->maxHealth) this->DrawHealthbar(50, 1.0f);


	//Enemy::Draw(); // draw hitbox
}

unsigned int WizardFireEnemy::GetLocalFramecount() const
{
	return this->localFramecount;
}
