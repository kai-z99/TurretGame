#pragma once

#include "Button.h"

class TryAgainButton : public Button
{
public:
	TryAgainButton(int x, int y);
	virtual void Draw() override;
	virtual void Update(int mouseX, int mouseY) override;

	static const char* tryAgainText;
	static const char* returnText;
	static int width;
	static int height;

private:
	virtual bool MouseCollide(int mouseX, int mouseY) override;
};