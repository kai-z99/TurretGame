#pragma once
#include "raylib.h"
#include <vector>
#include "helpers.h"

class Button;

class Hotbar
{
public:
	Hotbar();
	void Draw(GameStats* gameStats);
	void Update(unsigned int frame);

private:
	std::vector<Button*> buttons;
};