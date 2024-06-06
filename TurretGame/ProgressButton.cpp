#include "ProgressButton.h"
#include <string>

const int ProgressButton::width = 100;
const int ProgressButton::height = 100;

ProgressButton::ProgressButton(int posX, int posY, int id)
{
	this->position = { (float)posX, (float)posY };
	this->id = id;
}

void ProgressButton::Draw()
{
	//Draw bg square
	Color col;
	if (this->isHeld) col = DARKBLUE;
	else if (this->isHovering) col = { 0, 0, 255, 50 };
	else col = WHITE;

	DrawRectangle(this->position.x, this->position.y, this->width, this->height, col );

	//draw progress bar
	int w = 70;
	int h = 10;
	DrawRectangle((this->position.x + (ProgressButton::width / 2)) - (w / 2), this->position.y + 80, w, h, RED);
	DrawRectangle((this->position.x + (ProgressButton::width / 2)) - (w / 2), this->position.y + 80, w * progress, h, GREEN);


	//draw id, temp
	DrawText(std::to_string(this->id).c_str(), this->position.x, this->position.y, 20.0f, RED);
}

void ProgressButton::Update(int mouseX, int mouseY)
{
	Button::Update(mouseX, mouseY);
}

bool ProgressButton::MouseCollide(int mouseX, int mouseY)
{
	Rectangle rec = { this->position.x, this->position.y, this->width, this->height };
	return CheckCollisionPointRec({ (float)mouseX, (float)mouseY }, {rec});
}

void ProgressButton::SetProgress(float progress)
{
	this->progress = progress;
}