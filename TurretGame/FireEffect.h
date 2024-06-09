#pragma once
#include "VisualEffect.h"

class TextureLoop;

class FireEffect : public VisualEffect
{
public:
	FireEffect(Vector2 pos, float scale);
	virtual void UpdateAndDraw() override;

private:
	TextureLoop* textureLoop;
};
