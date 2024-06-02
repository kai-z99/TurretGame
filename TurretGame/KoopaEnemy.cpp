#include "KoopaEnemy.h"
#include "textures.h"

KoopaEnemy::KoopaEnemy()
{
	this->id = 2;
	this->damage = 3;
	this->health = 10;
	this->velocity = { -1.5,0 };
	this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 100 };

	//Texture init for animation state 1
	this->texture = &koopaTexture;
	this->textureWidth = this->texture->width;
	this->textureHeight = this->texture->height;
	this->textureSourceRec = { 0.0f, 0.0f, ((float)this->textureWidth / 2.0f), (float)this->textureHeight }; //first half of koopa.png is the first anim state
	this->textureDestRec = { this->position.x, this->position.y, ((float)this->textureWidth / 2.0f) * 4.0f, (float)this->textureHeight * 4.0f};
	this->textureOriginPoint = { (this->textureWidth / 2.0f) * 4.0f / 2.0f, this->textureHeight * 4.0f / 2.0f };

	this->animationState = 1;
}

void KoopaEnemy::Update(unsigned int frame)
{
	Enemy::Update(frame); // update position and velocity and check if death

	if (frame % 20 == 0) //update the animation state
	{
		if (this->animationState == 2) this->animationState = 1;
		else this->animationState++;
	}


	//update hitbox position
	this->hitbox = { this->position.x - (50 / 2), this->position.y - (100 / 2), 50, 100 };

	//update part of koopa we want to show based off anim state
	this->textureSourceRec = { ((float)this->textureWidth / 2.0f) * (this->animationState - 1), //x0
								0.0f,															//y0
								((float)this->textureWidth / 2.0f),								//x1
								(float)this->textureHeight };									//y1

	//update the destination rectangle
	this->textureDestRec = { this->position.x, this->position.y,
						 ((float)this->textureWidth / 2.0f) * 4.0f,
						 (float)this->textureHeight * 4.0f };
}

void KoopaEnemy::Draw()
{
	DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, 0, WHITE);

	//Enemy::Draw(); // draw hitbox
}