#pragma once
#include "raylib.h"

class Button
{
public:
	virtual void Draw();
	virtual void Update(int mouseX, int mouseY);

	bool isHovering;
	bool isClicked;
	bool isHeld;

protected:
	virtual bool MouseCollide(int mouseX, int mouseY) = 0;

	Vector2 position;
	
};