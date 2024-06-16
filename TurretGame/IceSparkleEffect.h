#pragma once

#include "VisualEffect.h"

class TextureLoop;

class IceSparkleEffect : public VisualEffect
{
public:
	IceSparkleEffect(Vector2 pos, float scale);
	virtual void UpdateAndDraw() override;

private:
	TextureLoop* textureLoop;
};