#include "WizardSparkleEffect.h"

#include "textures.h"
#include "TextureLoop.h"

WizardSparkleEffect::WizardSparkleEffect(Vector2 pos, float scale)
{
	this->position = pos;
	this->framesLeft = 70;
	this->textureLoop = new TextureLoop(&textures[26], 7, scale, pos);
	this->textureLoop->SetTint(RED);
}

void WizardSparkleEffect::UpdateAndDraw()
{
	if (this->framesLeft > 0)
	{
		this->textureLoop->Update();
		this->textureLoop->Draw();
		if (this->framesLeft != 6 || this->framesLeft != 5 || this->framesLeft != 4) this->textureLoop->NextFrame();

		this->framesLeft -= 1;
	}
}
