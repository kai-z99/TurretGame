#pragma once


#include "VisualEffect.h"

class TextureLoop;

class WizardSparkleEffect : public VisualEffect
{
public:
	WizardSparkleEffect(Vector2 pos, float scale);
	virtual void UpdateAndDraw() override;

private:
	TextureLoop* textureLoop;
};