#include "Button.h"

void Button::Draw()
{
	DrawRectangle((int)this->position.x, (int)this->position.y, 100, 100, RED);
	DrawText("BUTTON HERE", (int)this->position.x, (int)this->position.y, 30, RED);
}

void Button::Update(int mouseX, int mouseY)
{
	if (this->MouseCollide(mouseX, mouseY))
	{
		if (IsMouseButtonPressed(0))
		{
			this->isClicked = true;
			this->isHeld = false;
			this->isHovering = false;
			this->isReleased = false;
		}

		else if (IsMouseButtonDown(0))
		{
			this->isClicked = false;
			this->isHeld = true;
			this->isHovering = false;
			this->isReleased = false;
		}

		else if (IsMouseButtonReleased(0))
		{
			this->isClicked = false;
			this->isHeld = false;
			this->isHovering = true;
			this->isReleased = true;
		}

		else
		{
			this->isClicked = false;
			this->isHeld = false;
			this->isHovering = true;
			this->isReleased = false;
		}
	}

	else
	{
		this->isHovering = false;
		this->isClicked = false;
		this->isHeld = false;
		this->isReleased = false;
	}
}

void Button::SetPosition(int posX, int posY)
{
	this->position = { (float)posX, (float)posY };
}

Vector2 Button::GetPosition() const
{
	return this->position;
}


	
