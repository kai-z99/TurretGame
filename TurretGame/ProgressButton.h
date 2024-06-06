#pragma once
#include "Button.h"

class ProgressButton : public Button
{
public:
	ProgressButton(int posX, int posY, int id);

	virtual void Draw() override;
	virtual void Update(int mouseX, int mouseY) override;
	void SetProgress(float progress);

	static const int width;
	static const int height;

private:
	virtual bool MouseCollide(int mouseX, int mouseY);

	float progress = 0.0f;
	int id;
	Texture2D texture;

};

