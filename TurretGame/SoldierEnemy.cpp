#include "SoldierEnemy.h"
SoldierEnemy::SoldierEnemy()
{
	this->damage = 1;
	this->health = 4;
	this->velocity = { -4,0 };

	this->hitbox = { this->position.x, this->position.y, 50, 100 };

	//Texture init for animation state 1
	this->texture = LoadTexture("Sprites/scarfy.png");
	this->textureWidth = this->texture.width;
	this->textureHeight = this->texture.height;
	this->textureSourceRec = { 0.0f, 0.0f, (float)this->textureWidth / 6.0f, (float)this->textureHeight }; //first sixth of scarfy.png is the first anim state
	this->textureDestRec = { this->position.x, this->position.y, (float)this->textureWidth / 6, (float)this->textureHeight };
	this->textureOriginPoint = { (this->textureWidth / 6.0f) / 2.0f, this->textureHeight / 2.0f};

	this->animationState = 1;
}

void SoldierEnemy::Update(unsigned int frame)
{
	Enemy::Update(frame); // update position and velocity and check if death

	if (frame % 6 == 0) //update the animation state
	{
		if (this->animationState == 6) this->animationState = 1;
		else this->animationState++;
	}


	//update hitbox position
	this->hitbox = { this->position.x, this->position.y, 50, 100 };

	//update part of scarfy we want to show based off anim state
	this->textureSourceRec = { ((float)this->textureWidth / 6.0f) * (this->animationState - 1), //x0
								0.0f,															//y0
								((float)this->textureWidth / 6.0f),								//x1
								(float)this->textureHeight };									//y1

	//mirror scarfy's image to run left instead of right
	this->textureSourceRec.width = -this->textureSourceRec.width;

	//update the destination rectangle
	this->textureDestRec = { this->position.x, this->position.y,
						 (float)this->textureWidth / 6.0f,
						 (float)this->textureHeight };
}

void SoldierEnemy::Draw()
{
	DrawTexturePro(this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, 0, WHITE);

	Enemy::Draw(); // draw hitbox
}
