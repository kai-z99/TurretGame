#pragma once
#include "VisualEffect.h"

class TextureLoop;

class ExplosionEffect : public VisualEffect
{
public:
	ExplosionEffect(Vector2 pos);
	virtual void UpdateAndDraw() override;

private:
	TextureLoop* textureLoop;
};