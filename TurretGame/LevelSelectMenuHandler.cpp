#include "LevelSelectMenuHandler.h"

#include <string>

#include "constants.h"

#include "Game.h"
#include "LevelButton.h"
#include "Decoration.h"
#include "TextButton.h"
#include "SoundHandler.h"

#include "textures.h"

LevelSelectHandler::LevelSelectHandler(Game* g)
{
	this->game = g;

	this->localFramecount = 0;

	//inital states here
	this->worldMarkers[1] = worldBoundaries[0];
	this->worldMarkers[2] = worldBoundaries[1];
	this->worldMarkers[3] = worldBoundaries[2];

	for (const auto& [levelID, pos] : MapPositions::levelPositions)
	{
		g->levelButtons.push_back(new LevelButton(pos.x, pos.y, levelID));

		if (levelID == 6 || levelID == 12) g->levelButtons[levelID - 1]->isBoss = true;
	}

	for (const auto& [id,positions] : MapPositions::decorationPositions)
	{
		for (const Vector2& pos : positions)
		{
			this->game->decorations.push_back(new Decoration(id, (int)pos.x, (int)pos.y));
		}
	}

	this->backgroundColor = { 115, 161, 0 , 255 };
}

void LevelSelectHandler::Update(unsigned int frame)
{
	//prevents delta from bugging out, since its not updated properly when going in/out of levels
	if (this->localFramecount == 0)
	{
		this->StoreInitialPositions();
	}

	this->localFramecount++;

	Game* g = this->game;

	for (LevelButton* b : g->levelButtons)
	{
		b->Update((int)g->mousePos.x, (int)g->mousePos.y);
	}

	g->shopButton->Update((int)g->mousePos.x, (int)g->mousePos.y);
	g->quitButton->Update((int)g->mousePos.x, (int)g->mousePos.y);


	int boundaryX = 400;
	if (this->worldMarkers[1] > boundaryX) this->currentWorld = 1;
	else if (this->worldMarkers[1] <= boundaryX && this->worldMarkers[2] > boundaryX) this->currentWorld = 2;
	else if (this->worldMarkers[2] <= boundaryX && this->worldMarkers[3] > boundaryX) this->currentWorld = 3;

	switch (this->currentWorld)
	{
	case 1:
		this->backgroundColor = { 115, 161, 0 , 255 };
		break;

	case 2:
		this->backgroundColor = { 194, 165, 0 , 255 };
		break;

	case 3:
		this->backgroundColor = { 4, 120, 106 , 255 };
		break;

	default:
		this->backgroundColor = RAYWHITE;
		break;
	}

}

void LevelSelectHandler::Draw()
{
	Game* g = this->game;

	ClearBackground(this->backgroundColor);

	for (LevelButton* b : g->levelButtons)
	{
		b->Draw();
	}

	//decorations
	for (Decoration* d : g->decorations)
	{
		d->Draw();
	}

	g->shopButton->Draw();
	g->quitButton->Draw();

	std::string text = std::to_string(g->gameStats->totalCoins) + " C";
	int width = MeasureText(text.c_str(), 30);
	DrawText(text.c_str(), (240 / 2) - (width / 2), 150, 30, BLACK);

	text = "WORLD " + std::to_string(this->currentWorld);
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
		this->StoreInitialPositions();
	}
	
	if (IsMouseButtonDown(0))
	{
		deltaMouseX = initialMouseX - (int)g->mousePos.x;
		//deltaMouseY = initialMouseY - (int)g->mousePos.y; only change x

		if (deltaMouseX > 0)
		{
			this->UpdatePositionsWithDelta();
		}

		else if (deltaMouseX < 0) // mouse right
		{

			if (g->levelButtons[0]->GetPosition().x <= 200) //left is ok right is disabled
			{
				this->UpdatePositionsWithDelta();
			}

			else
			{
				this->StoreInitialPositions();
			}

		}
	}

	if (g->shopButton->isReleased)
	{
		g->shopButton->isReleased = false;
		g->gameState = UpgradeMenu;
	}

	else if (g->quitButton->isClicked)
	{
		g->quitButton->isReleased = false;
		g->gameState = MainMenu;
		g->soundHandler->HandleGoToMainMenu();
	}

	for (LevelButton* b : g->levelButtons)
	{
		if (b->isClicked)
		{
			g->currentLevel = b->GetLevel();
			g->gameState = InLevel;
			g->StartCurrentLevel();
			g->soundHandler->HandleEnterLevel(b->GetLevel());
			this->localFramecount = 0;
		}
	}
}

void LevelSelectHandler::StoreInitialPositions()
{
	Game* g = this->game;

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

	for (auto& [world,posX] : this->worldMarkers)
	{
		this->initialMarkerPositions[world] = posX;
	}

}

void LevelSelectHandler::UpdatePositionsWithDelta()
{
	Game* g = this->game;

	for (LevelButton* b : g->levelButtons)
	{
		b->SetPosition((int)this->initialLevelButtonPositions[b].x - deltaMouseX, (int)this->initialLevelButtonPositions[b].y - deltaMouseY);
	}

	for (Decoration* d : g->decorations)
	{
		d->SetPosition((int)this->initialDecorationPositions[d].x - deltaMouseX, (int)this->initialDecorationPositions[d].y - deltaMouseY);
	}

	for (auto& [world,posX] : this->worldMarkers)
	{
		posX = this->initialMarkerPositions[world] - deltaMouseX;
	}
}
