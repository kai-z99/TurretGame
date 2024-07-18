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

	//DrawCircleV(this->position, this->radius, col);

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

