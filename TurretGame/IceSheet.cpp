#include "IceSheet.h"
#include "Enemy.h"
#include "TextureLoop.h"
#include "textures.h"

IceSheet::IceSheet(int posX, int posY, int frames)
{
	this->id = 2;
	this->totalFrames = frames;
	this->framesLeft = this->totalFrames;
	this->position = { (float)posX, (float)posY };
	this->width = 700;
	this->height = 300;

	this->hitbox = { this->position.x - this->width / 2, this->position.y - height / 2, (float)this->width, (float)this->height };
	this->isActive = true;

	this->textureLoop = new TextureLoop(&textures[14], 5, 1.0f, this->position);
	this->alphaModifier = 0.0f;
	
}

void IceSheet::Update(unsigned int frame)
{
	if (this->framesLeft > 0)
	{
		//if its on its first 30 frames, fade in
		if (this->totalFrames - this->framesLeft < 30)
		{
			alphaModifier += 0.03f;
		}

		//if its on the last 2 seconds, fade out
		else if (this->framesLeft < 120)
		{
			alphaModifier -= 0.0073f;
		}

		this->framesLeft--;
	}

	else this->isActive = false;

	
	

	
}

void IceSheet::Draw()
{
	int alpha = (int)(70 * this->alphaModifier);
	if (alpha < 0) alpha = 0;
	DrawRectangleRec(this->hitbox, { 87, 157, 255,(unsigned char)alpha});
}

bool IceSheet::EnemyCollided(Enemy* e)
{
	return CheckCollisionRecs(this->hitbox, e->GetHitbox());
}

Rectangle IceSheet::GetHitbox() const
{
	return this->hitbox;
}

