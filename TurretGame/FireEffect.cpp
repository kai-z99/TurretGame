#include "FireEffect.h"
#include "TextureLoop.h"
#include "textures.h"

FireEffect::FireEffect(Vector2 pos, float scale)
{
	this->position = pos;
	this->framesLeft = 8;
	this->textureLoop = new TextureLoop(&textures[11], 8, scale, pos);
}

void FireEffect::UpdateAndDraw()
{
	if (this->framesLeft > 0)
	{
		this->textureLoop->Update();
		this->textureLoop->Draw();
		this->textureLoop->NextFrame();

		this->framesLeft -= 1;
	}
}
