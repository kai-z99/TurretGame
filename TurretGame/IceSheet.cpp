#include "IceSheet.h"
#include "Enemy.h"
#include "TextureLoop.h"
#include "textures.h"

int IceSheet::width = 500;
int IceSheet::height = 300;
int IceSheet::duration = 240;
int IceSheet::intensity = 5;

IceSheet::IceSheet(int posX, int posY)
{
	this->id = 2;

	this->framesLeft = IceSheet::duration;
	this->position = { (float)posX, (float)posY };

	this->hitbox = { this->position.x - IceSheet::width / 2, this->position.y - IceSheet::height / 2, (float)IceSheet::width, (float)IceSheet::height };
	this->isActive = true;

	this->textureLoop = new TextureLoop(&textures[14], 5, 1.0f, this->position);
	this->alphaModifier = 0.0f;
	
}

void IceSheet::Update(unsigned int frame)
{
	if (this->framesLeft > 0)
	{
		//if its on its first 30 frames, fade in
		if (IceSheet::duration - this->framesLeft < 30)
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

