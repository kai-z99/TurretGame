#pragma once
#include <unordered_map>
#include "raylib.h"

class Game;
class LevelButton;

class LevelSelectHandler
{
public:
	LevelSelectHandler(Game* g);

	void Update(unsigned int frame);
	void Draw();
	void HandleInput();

private:
	Game* game;

	int initialMouseX;
	int initialMouseY;

	int deltaMouseX;
	int deltaMouseY;

	std::unordered_map<LevelButton*, Vector2> initialLevelButtonPositions;
};