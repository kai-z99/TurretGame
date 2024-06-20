#include "WolfEnemy.h"
#include "textures.h"
#include "TextureLoop.h"

WolfEnemy::WolfEnemy()
{
	this->id = 4;
	this->damage = 8;
	this->maxHealth = 18;
	this->health = this->maxHealth;
	this->coinDropAmount = GetRandomValue(30, 51);

	this->knockbackMultiplier = 1.0f;
	this->baseVelocity = { -1.5,0.0f };
	this->currentVelocity = this->baseVelocity;
	this->hitbox = { this->position.x - (100 / 2), this->position.y - (50 / 2), 100, 50 }; //50 and 100 are the hitbox dimensions... minus half for centering purpose
	this->textureLoop = new TextureLoop(&textures[16], 4, 2.6f, this->position);

	this->runThreshold = GetRandomValue(1100,1600); //x
	this->runFrames = 0;
	this->runSpeed = -5.5f;
	this->ran = false;

	this->runTexture = new TextureLoop(&textures[17], 5, 2.6f, this->position);
}

void WolfEnemy::Update(unsigned int frame)
{
	// update position and velocity and check if death
	Enemy::Update(frame);

	//update postion of texture
	this->textureLoop->SetPosition((int)this->position.x, (int)this->position.y);
	this->runTexture->SetPosition((int)this->position.x, (int)this->position.y);

	//if the wolf hasnt run yet and its past the threahold, make it run
	if (this->ran == false && this->position.x < this->runThreshold)
	{
		this->ran = true;
		this->runFrames += 120;
	}
		
	//  make the wolf faster when its running
	if (this->runFrames > 0 && this->currentVelocity.x != this->runSpeed)
	{
		this->currentVelocity.x = this->runSpeed;
		this->runFrames--;
	}
		
	else this->currentVelocity.x = this->baseVelocity.x;

	//update the animation state
	if (frame % 20 == 0)
	{
		this->textureLoop->NextFrame();
	}

	if (frame % 5 == 0)
	{
		this->runTexture->NextFrame();
	}
		
		
	//update hitbox position
	//this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 100 };
	this->hitbox.x = this->position.x - (100 / 2);
	this->hitbox.y = this->position.y - (50 / 2);

	//update texture proteries based on new position
	this->textureLoop->Update();

	this->runTexture->SetTint(this->tint);
	this->runTexture->Update();

}

void WolfEnemy::Draw()
{
	if (this->runFrames <= 0) this->textureLoop->Draw();
	else this->runTexture->Draw();
	//DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, 0, WHITE);
	if (this->health < this->maxHealth) this->DrawHealthbar(50, 1.0f);


	//Enemy::Draw(); // draw hitbox
}
