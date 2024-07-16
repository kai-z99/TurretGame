#include "MainMenuHandler.h"

#include "constants.h"
#include "Game.h"
#include "SoundHandler.h"

#include "TextButton.h"

MainMenuHandler::MainMenuHandler(Game* game)
{
	this->game = game;
}

void MainMenuHandler::Update(unsigned int frame)
{
	Game* g = this->game;

	g->startButton->Update((int)g->mousePos.x, (int)g->mousePos.y);
}

void MainMenuHandler::Draw()
{
	const char* text = "TURRET FORCE I";
	int width = MeasureText(text, 80);
	DrawText(text, (screenWidth / 2) - (width / 2), (screenHeight / 2) - 300, 80, BLACK);

	this->game->startButton->Draw();
}

void MainMenuHandler::HandleInput()
{
	Game* g = this->game;

	if (g->startButton->isReleased)
	{
		g->startButton->isReleased = false;
		g->gameState = LevelSelectMenu;
		g->soundHandler->HandleGoToLevelSelect();
	}
}
