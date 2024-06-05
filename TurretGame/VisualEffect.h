#pragma once
#include "raylib.h"

class VisualEffect
{
public:
	virtual void UpdateAndDraw();

protected:
	Vector2 position;
	int framesLeft;
};
