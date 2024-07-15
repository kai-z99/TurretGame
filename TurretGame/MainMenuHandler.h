#pragma once

class Game;

class MainMenuHandler
{
public:
	MainMenuHandler(Game* game);

	void Update(unsigned int frame);

	void Draw();

	void HandleInput();

private:
	Game* game;
};