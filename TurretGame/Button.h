#pragma once
#include "raylib.h"

class Button
{
public:
	virtual void Draw();
	virtual void Update(int mouseX, int mouseY);

	bool isReleased = false;
	bool isHovering = false;
	bool isClicked = false;
	bool isHeld = false; 

	virtual void SetPosition(int posX, int posY);
	Vector2 GetPosition() const;
protected:
	virtual bool MouseCollide(int mouseX, int mouseY) = 0;

	Vector2 position;
};