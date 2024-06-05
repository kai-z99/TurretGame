#pragma once
#include "raylib.h"
#include <vector>

class VisualEffect;

class VisualEffectsManager
{
public:
	VisualEffectsManager();
	void DisplayCoinSplash(Vector2 pos, int amount);
	void DisplayExplosion(Vector2 pos);
	void UpdateAndDraw();

private:
	std::vector<VisualEffect*> tasks; // animationtype, frames remaining

};