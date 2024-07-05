#include "SparkleEffect.h"

#include "TextureLoop.h"
#include "textures.h"

SparkleEffect::SparkleEffect(Vector2 pos, float scale)
{
	this->position = pos;
	this->framesLeft = 7;
	this->textureLoop = new TextureLoop(&textures[26], 7, scale, pos);
}

void SparkleEffect::UpdateAndDraw()
{
	if (this->framesLeft > 0)
	{
		this->textureLoop->Update();
		this->textureLoop->Draw();
		this->textureLoop->NextFrame();

		this->framesLeft -= 1;
	}

}
