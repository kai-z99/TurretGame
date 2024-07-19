#include "BlueFireEffect.h"

#include "TextureLoop.h"
#include "textures.h"

BlueFireEffect::BlueFireEffect(Vector2 pos, float scale)
{
	this->position = pos;
	this->framesLeft = 8;
	this->textureLoop = new TextureLoop(&textures[51], 4, scale, pos);
}

void BlueFireEffect::UpdateAndDraw()
{

	if (this->framesLeft > 0)
	{
		this->textureLoop->Update();
		this->textureLoop->Draw();
		if (this->framesLeft % 2 == 0) this->textureLoop->NextFrame();

		this->framesLeft -= 1;
	}
}
