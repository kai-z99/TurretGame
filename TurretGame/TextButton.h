#pragma once

#include "Button.h"

class TextButton : public Button
{
public:
	TextButton(int x, int y, const char* text);
	virtual void Draw() override;
	virtual void Update(int mouseX, int mouseY) override;

	static const char* tryAgainText;
	static const char* returnText;
	static int width;
	static int height;

private:
	virtual bool MouseCollide(int mouseX, int mouseY) override;
	const char* text;
};