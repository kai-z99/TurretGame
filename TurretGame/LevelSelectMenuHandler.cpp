#include "LevelSelectMenuHandler.h"

#include <string>

#include "constants.h"

#include "Game.h"
#include "LevelButton.h"
#include "Decoration.h"

#include "textures.h"

LevelSelectHandler::LevelSelectHandler(Game* g)
{
	this->game = g;

	//temp

	//inital states here
	this->worldMarkers[1] = worldBoundaries[0];
	this->worldMarkers[2] = worldBoundaries[1];
	this->worldMarkers[3] = worldBoundaries[2];

	g->levelButtons.push_back(new LevelButton(200, 500, 1));
	g->levelButtons.push_back(new LevelButton(700, 700, 2));
	g->levelButtons.push_back(new LevelButton(500, 500, 3));
	g->levelButtons.push_back(new LevelButton(1000, 550, 4));
	g->levelButtons.push_back(new LevelButton(1200, 400, 5));
	g->levelButtons.push_back(new LevelButton(1400, 600, 6));

	//0: grass1
	std::vector<Vector2> grass1Positions = { {100,500},{2000,200},{700,300}, {1159,781}, {1590, 245} };
	//1: grass2
	std::vector<Vector2> grass2Positions = { {800,500},{750,200},{500,100}, {260, 830} };
	//2: bush
	std::vector<Vector2> bushPositions = { {260,500},{700,1000}, {1500, 800} };

	for (const Vector2& pos : grass1Positions)
	{
		this->decorationPositionMap[0].push_back(pos);
	}

	for (const Vector2& pos : grass2Positions)
	{
		this->decorationPositionMap[1].push_back(pos);
	}

	for (const Vector2& pos : bushPositions)
	{
		this->decorationPositionMap[2].push_back(pos);
	}

	for (const auto& pair : this->decorationPositionMap)
	{
		for (const Vector2& pos : pair.second)
		{
			this->game->decorations.push_back(new Decoration(pair.first, pos.x, pos.y));
		}
	}
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


	int boundaryX = 400;
	if (this->worldMarkers[1] > boundaryX) this->currentWorld = 1;
	else if (this->worldMarkers[1] <= boundaryX && this->worldMarkers[2] > boundaryX) this->currentWorld = 2;
	else if (this->worldMarkers[2] <= boundaryX && this->worldMarkers[3] > boundaryX) this->currentWorld = 3;

}

void LevelSelectHandler::Draw()
{
	Game* g = this->game;

	for (LevelButton* b : g->levelButtons)
	{
		b->Draw();
	}

	//decorations
	for (Decoration* d : g->decorations)
	{
		d->Draw();
	}


	DrawText(std::to_string(g->gameStats->totalCoins).c_str(), 10, 10, 30, BLUE);

	std::string text = "WORLD " + std::to_string(this->currentWorld);
	DrawText(text.c_str(), screenWidth / 2 - 70, 50, 50, BLACK);
	
	//debug
	//for (auto& x : this->worldMarkers)
	//{
	//	DrawLine(x.second, 0, x.second, screenHeight, RED);
	//}
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

		for (Decoration* d : g->decorations)
		{
			this->initialDecorationPositions[d] = d->GetPosition();
		}

		for (auto& x : this->worldMarkers)
		{
			this->initialMarkerPositions[x.first] = x.second;
		}
	}
	
	if (IsMouseButtonDown(0))
	{
		deltaMouseX = initialMouseX - (int)g->mousePos.x;
		//deltaMouseY = initialMouseY - (int)g->mousePos.y; only change x

		if (g->levelButtons[0]->GetPosition().x <= 200 || deltaMouseX > 0 || 1) //temp , should prevent scrolling
		{
			for (LevelButton* b : g->levelButtons)
			{
				b->SetPosition((int)this->initialLevelButtonPositions[b].x - deltaMouseX, (int)this->initialLevelButtonPositions[b].y - deltaMouseY);
			}

			for (Decoration* d : g->decorations)
			{
				d->SetPosition((int)this->initialDecorationPositions[d].x - deltaMouseX, (int)this->initialDecorationPositions[d].y - deltaMouseY);
			}

			for (auto& x : this->worldMarkers)
			{
				x.second = this->initialMarkerPositions[x.first] - deltaMouseX;
			}
		}		
	}


}
