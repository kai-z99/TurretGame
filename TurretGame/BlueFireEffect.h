#pragma once

#include "VisualEffect.h"

class TextureLoop;

class BlueFireEffect : public VisualEffect
{
public:
	BlueFireEffect(Vector2 pos, float scale);
	virtual void UpdateAndDraw() override;

private:
	TextureLoop* textureLoop;
};
