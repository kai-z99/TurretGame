#pragma once
#include "raylib.h"

class TextureLoop;

class AreaEffect
{
public:
	virtual void Update(unsigned int frame);
	virtual void Draw();

	int GetID();
	Vector2 GetPosition() const;
	bool isActive;
	int framesLeft;

protected:
	Vector2 position;
	TextureLoop* textureLoop;
	int id;
};