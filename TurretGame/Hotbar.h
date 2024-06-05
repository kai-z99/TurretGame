#pragma once
#include "raylib.h"
#include "helpers.h"

class Hotbar
{
public:
	Hotbar();
	void Draw(GameStats* gameStats);
	void Update(unsigned int frame);
};