#include "TryAgainButton.h"

const char* TryAgainButton::tryAgainText = "TRY AGAIN";
const char* TryAgainButton::returnText = "RETURN TO MENU";
int TryAgainButton::height = 150;
int TryAgainButton::width = 400;

TryAgainButton::TryAgainButton(int x, int y)
{
	this->position = { (float)x, (float)y, };
}

void TryAgainButton::Draw()
{
	Color col = WHITE;
	if (this->isHovering) col = { 122, 234, 240 , 255 };
	else if (this->isHeld) col = BLUE;

	DrawRectangleV({ this->position.x - 15.0f, this->position.y - 15.0f }, { (float)TryAgainButton::width, (float)TryAgainButton::height }, BLUE);
	DrawRectangleV(this->position, { (float)TryAgainButton::width - 30.0f, (float)TryAgainButton::height - 30.0f }, col);
	
	int x = (int)this->position.x + (int)(TryAgainButton::width / 2) - (MeasureText(TryAgainButton::tryAgainText, 40) / 2) - 15;
	int y = (int)this->position.y + (int)(TryAgainButton::height / 2) - 30;
	DrawText(TryAgainButton::tryAgainText, x, y, 40, BLACK);	
}

void TryAgainButton::Update(int mouseX, int mouseY)
{
	Button::Update(mouseX, mouseY);
}

bool TryAgainButton::MouseCollide(int mouseX, int mouseY)
{
	Rectangle rec = { this->position.x, this->position.y, TryAgainButton::width, TryAgainButton::height };
	return CheckCollisionPointRec({ (float)mouseX, (float)mouseY }, rec);
}
