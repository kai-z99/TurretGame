#pragma once

#include "VisualEffect.h"

class TextureLoop;

class SparkleEffect : public VisualEffect
{
public:
	SparkleEffect(Vector2 pos, float scale);
	virtual void UpdateAndDraw() override;

private:
	TextureLoop* textureLoop;
};