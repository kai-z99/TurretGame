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
		g->levelButtons.push_back(new LevelButton((int)pos.x, (int)pos.y, levelID, false));

		if (levelID == 6 || levelID == 12) g->levelButtons[levelID - 1]->isBoss = true;

		//if the level is compelte, set it to compelte
		if (g->gameStats->levelCompletions[levelID] == true) g->levelButtons[levelID - 1]->isComplete = true;
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
	g->shopButton->SetPosition(10,(menuBoundaryY / 2) - (130 / 2));

	g->quitButton->SetText("BACK");
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

	//set states of level buttons
	for (const auto& [level, complete] : g->gameStats->levelCompletions)
	{
		LevelButton* button = g->levelButtons[level - 1];

		//if the level is compelte, set button to compelte
		if (complete)
		{
			button->isComplete = true;

			//completed level always availble to play
			button->isAvailible = true;
		}

		//if the level is not complete, set button to incomplete.
		else
		{
			button->isComplete = false;

			// if the previous level is compelte, set the level to availible.
			if (level == 1 || g->gameStats->levelCompletions[level - 1] == true) button->isAvailible = true;
		}
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

		if (deltaMouseX > 0) //m left
		{
			if (g->levelButtons[11]->GetPosition().x > screenWidth - 200) // okay to move
			{
				this->UpdatePositionsWithDelta();
			}

			else
			{
				this->StoreInitialPositions();
			}
		}

		else if (deltaMouseX < 0) // mouse right
		{

			if (g->levelButtons[0]->GetPosition().x <= 200) //left is ok right is disabled. okay to move.
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
		if (b->isClicked && b->isAvailible)
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
