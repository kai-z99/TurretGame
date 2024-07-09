#include "SpinBirdEnemy.h"

#include "textures.h"
#include "TextureLoop.h"

#include "BalloonBossEnemy.h"

#include "helpers.h"

SpinBirdEnemy::SpinBirdEnemy(BalloonBossEnemy* host)
{
	this->id = 9;
	this->damage = 5;
	this->maxHealth = 7777777777.7f;
	this->health = this->maxHealth;
	this->coinDropAmount = GetRandomValue(1, 2);

	this->host = host;

	this->knockbackMultiplier = 0.0f;
	this->baseVelocity = this->host->GetBaseVelocity();
	this->currentVelocity = this->baseVelocity;
	this->hitbox = { this->position.x - (60 / 2), this->position.y - (50 / 2), 60, 60 }; //50 and 100 are the hitbox dimensions... minus half for centering purpose
	this->textureLoop = new TextureLoop(&textures[36], 8, 3.0f, this->position);

	this->textureLoop->SetRotationOffset(-90.0f);

	this->resistChill = true;
}

void SpinBirdEnemy::Update(unsigned int frame)
{
	if (!this->host->isActive)
	{
		this->isActive = false;
	}

	// update position and velocity and check if death
	Enemy::Update(frame);

	//rotate around host boss
	this->currentVelocity = this->host->currentVelocity;
	this->position = RotatePoint(this->position, host->GetPosition(), -0.03f);

	//update postion of texture
	this->textureLoop->SetPosition((int)this->position.x, (int)this->position.y);

	//update angle of texture
	this->textureLoop->SetRotation(CalculateAngle((int)this->host->position.x, (int)this->host->position.y, (int)this->position.x, (int)this->position.y) * RAD2DEG);

	//update the animation state
	if (frame % 10 == 0) this->textureLoop->NextFrame();

	//update hitbox position
	//this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 100 };
	this->hitbox.x = this->position.x - (60 / 2.0f);
	this->hitbox.y = this->position.y - (60 / 2.0f);

	//update texture proteries based on new position
	this->textureLoop->Update();
}

void SpinBirdEnemy::Draw()
{
	this->textureLoop->Draw();
	//DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, 0, WHITE);
	//if (this->health < this->maxHealth) this->DrawHealthbar(50, 1.0f);

	//Enemy::Draw();

}


