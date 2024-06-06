#include "ExplosionEffect.h"
#include "TextureLoop.h"
#include "textures.h"

ExplosionEffect::ExplosionEffect(Vector2 pos)
{
	this->position = pos;
	this->framesLeft = 10;
	this->textureLoop = new TextureLoop(&textures[9], 9, 1.0f, pos);
}

void ExplosionEffect::UpdateAndDraw()
{
	if (this->framesLeft > 0)
	{
		this->textureLoop->Update();
		this->textureLoop->Draw();
		this->textureLoop->NextFrame();
		
		this->framesLeft -= 1;
	}

}
