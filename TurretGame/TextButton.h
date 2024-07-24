#pragma once

#include "Button.h"

class TextButton : public Button
{
public:
	TextButton(Rectangle rec, const char* text);
	TextButton(int posX, int posY, int w, int h, const char* text);

	virtual void Draw() override;
	virtual void Update(int mouseX, int mouseY) override;

	virtual void SetPosition(int posX, int posY) override;

private:
	virtual bool MouseCollide(int mouseX, int mouseY) override;
	const char* text;
	Rectangle rec;
};