#include "UpgradeButton.h"
#include <string>

const int UpgradeButton::width = 100;
const int UpgradeButton::height = 100;

UpgradeButton::UpgradeButton(int posX, int posY, int id)
{
	this->position = { (float)posX, (float)posY };
	this->id = id;
}

void UpgradeButton::Draw()
{
	Color col;
	if (this->isHeld) col = DARKBLUE;
	else if (this->isHovering) col = { 0, 0, 255, 50 };
	else col = WHITE;

	DrawRectangle(this->position.x, this->position.y, this->width, this->height, col );

	int w = 70;
	int h = 10;

	DrawRectangle((this->position.x + (UpgradeButton::width / 2)) - (w / 2), this->position.y + 80, w, h, RED);
	DrawRectangle((this->position.x + (UpgradeButton::width / 2)) - (w / 2), this->position.y + 80, w * progress, h, GREEN);

	DrawText(std::to_string(this->id).c_str(), this->position.x, this->position.y, 20.0f, RED);
}

void UpgradeButton::Update(int mouseX, int mouseY)
{
	Button::Update(mouseX, mouseY);
}

bool UpgradeButton::MouseCollide(int mouseX, int mouseY)
{
	Rectangle rec = { this->position.x, this->position.y, this->width, this->height };
	return CheckCollisionPointRec({ (float)mouseX, (float)mouseY }, {rec});
}

void UpgradeButton::SetProgress(float progress)
{
	this->progress = progress;
}