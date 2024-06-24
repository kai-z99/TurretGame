#include "LevelButton.h"
#include <string>

LevelButton::LevelButton(int posX, int posY, int level)
{
	this->position = { (float)posX, (float)posY };
	this->radius = 30.0f;
	this->level = level;
}

void LevelButton::Draw()
{
	Color col;

	if (this->isHovering) col = BLUE;
	else col = RED;

	DrawCircleV(this->position, this->radius, col);
	DrawText(std::to_string(this->level).c_str(), this->position.x, this->position.y, 30, GREEN);
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

