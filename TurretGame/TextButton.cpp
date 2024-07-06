#include "TextButton.h"

int TextButton::height = 150;
int TextButton::width = 400;

TextButton::TextButton(int x, int y, const char* text)
{
	this->position = { (float)x, (float)y, };
	this->text = text;
}

void TextButton::Draw()
{
	Color col = WHITE;
	if (this->isHovering) col = { 122, 234, 240 , 255 };
	else if (this->isHeld) col = BLUE;

	DrawRectangleV({ this->position.x - 15.0f, this->position.y - 15.0f }, { (float)TextButton::width, (float)TextButton::height }, RED);
	DrawRectangleV(this->position, { (float)TextButton::width - 30.0f, (float)TextButton::height - 30.0f }, col);
	
	int x = (int)this->position.x + (int)(TextButton::width / 2) - (MeasureText(this->text, 35) / 2) - 15;
	int y = (int)this->position.y + (int)(TextButton::height / 2) - 30;
	DrawText(this->text, x, y, 35, RED);	
}

void TextButton::Update(int mouseX, int mouseY)
{
	Button::Update(mouseX, mouseY);
}

bool TextButton::MouseCollide(int mouseX, int mouseY)
{
	Rectangle rec = { this->position.x, this->position.y, TextButton::width, TextButton::height };
	return CheckCollisionPointRec({ (float)mouseX, (float)mouseY }, rec);
}
