#include "TextButton.h"

TextButton::TextButton(Rectangle rec, const char* text)
{
	this->rec = rec;
	this->text = text;
	this->position = { rec.x, rec.y };
}

TextButton::TextButton(int posX, int posY, int w, int h, const char* text)
{
	this->rec = { (float)posX, (float)posY, (float)w, (float)h };
	this->text = text;
	this->position = { (float)posX,(float)posY };
}

void TextButton::Draw()
{
	Color col = WHITE;
	if (this->isHovering) col = { 122, 234, 240 , 255 };
	else if (this->isHeld) col = BLUE;

	//DrawRectangle(this->rec.x - 15.0f, this->rec.y - 15.0f, this->rec.width + 30.0f, this->rec.height + 30.0f, BLACK);
	//DrawRectangleRec(this->rec, col);
	//

	DrawRectangleRec(this->rec, BLACK);
	DrawRectangle((int)this->rec.x + 15, (int)this->rec.y + 15, (int)this->rec.width - 30, (int)this->rec.height - 30, col);

	int x = (int)this->position.x + (int)(this->rec.width / 2) - (MeasureText(this->text, 35) / 2);
	int y = (int)this->position.y + (int)(this->rec.height / 2) - 11;
	DrawText(this->text, x, y, 35, BLACK);	
}

void TextButton::Update(int mouseX, int mouseY)
{
	Button::Update(mouseX, mouseY);
}

void TextButton::SetPosition(int posX, int posY)
{
	Button::SetPosition(posX, posY);
	this->rec.x = this->position.x;
	this->rec.y = this->position.y;
}

bool TextButton::MouseCollide(int mouseX, int mouseY)
{
	return CheckCollisionPointRec({ (float)mouseX, (float)mouseY }, this->rec);
}
