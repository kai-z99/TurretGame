#pragma once
#include "raylib.h"

class VisualEffect
{
public:
	virtual void UpdateAndDraw();
	bool isActive();

protected:
	Vector2 position;
	int framesLeft;
};
