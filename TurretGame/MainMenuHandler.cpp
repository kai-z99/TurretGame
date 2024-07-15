#include "MainMenuHandler.h"

#include "constants.h"
#include "Game.h"
#include "SoundHandler.h"

MainMenuHandler::MainMenuHandler(Game* game)
{
	this->game = game;
}

void MainMenuHandler::Update(unsigned int frame)
{
}

void MainMenuHandler::Draw()
{
	DrawText("GAME TITLE", screenWidth / 2, screenHeight / 2, 60, RED);
}

void MainMenuHandler::HandleInput()
{
	if (IsKeyPressed(KEY_ENTER))
	{
		this->game->gameState = LevelSelectMenu;
		this->game->soundHandler->HandleGoToLevelSelect();
	}
}
