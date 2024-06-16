#include "IceSparkleEffect.h"
#include "TextureLoop.h"
#include "textures.h"

IceSparkleEffect::IceSparkleEffect(Vector2 pos, float scale)
{
	this->position = pos;
	this->framesLeft = 7;
	this->textureLoop = new TextureLoop(&textures[14], 5, scale, pos);
}

void IceSparkleEffect::UpdateAndDraw()
{
	if (this->framesLeft > 0)
	{
		this->textureLoop->Update();
		this->textureLoop->Draw();
		if (this->framesLeft != 6 || this->framesLeft != 5 || this->framesLeft != 4) this->textureLoop->NextFrame();

		this->framesLeft -= 1;
	}

}