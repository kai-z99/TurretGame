#include "LevelButton.h"
#include <string>

LevelButton::LevelButton(int posX, int posY, int level, bool complete)
{
	this->position = { (float)posX, (float)posY };
	this->radius = 30.0f;
	this->level = level;
	this->isComplete = complete;
}

void LevelButton::Draw()
{
	Color col;

	if (this->isHovering)
	{
		if (this->isComplete) col = DARKBLUE;
		else
		{
			if (this->isAvailible) col = ORANGE;
			else col = DARKGRAY;
		}
	}
		
	else

	{
		if (this->isComplete) col = BLUE;
		else
		{
			if (this->isAvailible)col = RED;
			else col = DARKGRAY;
		}
	}

	DrawEllipse((int)this->position.x, (int)this->position.y, this->radius + 10.0f, this->radius, BLACK);
	DrawEllipse((int)this->position.x, (int)this->position.y, this->radius + 3.0f , this->radius - 7.0f, col);
	if (this->isBoss) DrawEllipse((int)this->position.x, (int)this->position.y, this->radius - 7.0f, this->radius - 17.0f, BLACK);


	DrawText(std::to_string(this->level).c_str(), (int)this->position.x, (int)this->position.y, 30, GREEN);
}

void LevelButton::Update(int mouseX, int mouseY)
{
	//mouseup, down etc
	Button::Update(mouseX, mouseY);
}

int LevelButton::GetLevel() const
{
	return this->level;
}

bool LevelButton::MouseCollide(int mouseX, int mouseY)
{
	return CheckCollisionPointCircle({(float)mouseX, (float)mouseY}, this->position, this->radius);
}

