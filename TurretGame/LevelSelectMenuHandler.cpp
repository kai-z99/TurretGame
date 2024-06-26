#include "LevelSelectMenuHandler.h"
#include <string>

#include "constants.h"

#include "Game.h"
#include "LevelButton.h"

LevelSelectHandler::LevelSelectHandler(Game* g)
{
	this->game = g;

	//temp

	//inital states here
	g->levelButtons.push_back(new LevelButton(500, 500, 1));
	g->levelButtons.push_back(new LevelButton(700, 700, 2));
	g->levelButtons.push_back(new LevelButton(200, 500, 3));
	g->levelButtons.push_back(new LevelButton(500, 900, 4));
}

void LevelSelectHandler::Update(unsigned int frame)
{
	Game* g = this->game;

	for (LevelButton* b : g->levelButtons)
	{
		b->Update((int)g->mousePos.x, (int)g->mousePos.y);

		if (b->isClicked)
		{
			g->currentLevel = b->GetLevel();
			g->gameState = InLevel;
			g->StartCurrentLevel();
		}
	}
}

void LevelSelectHandler::Draw()
{
	Game* g = this->game;

	for (LevelButton* b : g->levelButtons)
	{
		b->Draw();
	}

	DrawText(std::to_string(g->gameStats->totalCoins).c_str(), 10, 10, 30, BLUE);
	DrawText("WORLD 1", screenWidth / 2 - 70, 50, 50, BLACK);
}

void LevelSelectHandler::HandleInput()
{
	Game* g = this->game;

	if (IsMouseButtonPressed(0))
	{
		initialMouseX = (int)g->mousePos.x;
		initialMouseY = (int)g->mousePos.y;
		

		for (LevelButton* l : g->levelButtons)
		{
			this->initialLevelButtonPositions[l] = l->GetPosition();
		}
	}
	
	if (IsMouseButtonDown(0))
	{
		deltaMouseX = initialMouseX - (int)g->mousePos.x;
		deltaMouseY = initialMouseY - (int)g->mousePos.y;

		for (LevelButton* b : g->levelButtons)
		{
			b->SetPosition((int)this->initialLevelButtonPositions[b].x - deltaMouseX, (int)this->initialLevelButtonPositions[b].y - deltaMouseY);
		}
	}
}
