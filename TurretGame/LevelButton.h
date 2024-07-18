#pragma once

#include "Button.h"

class LevelButton : public Button
{
public:
	LevelButton(int posX, int posY, int level);

	virtual void Draw() override;
	virtual void Update(int mouseX, int mouseY) override;

	int GetLevel() const;

	bool isBoss = false;

private:
	virtual bool MouseCollide(int mouseX, int mouseY);

	float radius;

	int level;
};