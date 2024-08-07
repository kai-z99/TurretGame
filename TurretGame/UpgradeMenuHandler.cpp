#include "UpgradeMenuHandler.h"
#include <iostream>
#include <string>

#include "constants.h"
#include "types.h"
#include "helpers.h"
#include "Database.h"

#include "Game.h"
#include "UpgradeButton.h"
#include "Turret.h"
#include "Sentry.h"
#include "TurretLaser.h"
#include "IceSheet.h"
#include "BombExplosion.h"
#include "TextButton.h"

#include "textures.h"

UpgradeMenuHandler::UpgradeMenuHandler(Game* g)
{
	this->game = g;

	//bullets
	for (int i = 0; i <= 5; i++)
	{
		this->game->upgradeButtons.push_back(new UpgradeButton(130 * i + 300, 500, (Upgrade)i));
		this->game->upgradeButtons[i]->SetPrice(this->game->gameStats->upgradeStates[Upgrade(i)].second);
	}

	//abilities
	for (int i = 6; i <= 10; i++)
	{
		this->game->upgradeButtons.push_back(new UpgradeButton(130 * i + 300, 800, (Upgrade)i));
		this->game->upgradeButtons[i]->SetPrice(this->game->gameStats->upgradeStates[Upgrade(i)].second);
	}

}

void UpgradeMenuHandler::Update()
{
	Game* g = this->game;

	for (UpgradeButton* u : this->game->upgradeButtons)
	{
		u->Update((int)g->mousePos.x, (int)g->mousePos.y);

		if (u->isClicked && (g->gameStats->totalCoins >= u->GetPrice()))
		{

			//subtract coins
			this->game->gameStats->totalCoins -= u->GetPrice();

			//increase levl
			this->game->gameStats->upgradeStates[u->GetUpgrade()].first += 1;

			//increase the cost
			this->game->gameStats->upgradeStates[u->GetUpgrade()].second += (int)(10 + UpgradeDatabase::currentUpgradeInfo[u->GetUpgrade()].second * 0.2);

			//use that new db info to set game stats
			g->SetDatabaseValuesToGameStats();

			//set new price of button
			g->upgradeButtons[u->GetUpgrade()]->SetPrice(this->game->gameStats->upgradeStates[u->GetUpgrade()].second);

		}
	}

	g->quitButton->Update((int)g->mousePos.x, (int)g->mousePos.y);
}

void UpgradeMenuHandler::Draw()
{
	Game* g = this->game;
	std::string text = "Upgrade!";
	int width = MeasureText(text.c_str(), 50);
	DrawText("Upgrade!", screenWidth / 2 - (width / 2), 100, 50, BLACK);

	text = std::to_string(g->gameStats->totalCoins) + " C";
	width = MeasureText(text.c_str(), 40);
	DrawText(text.c_str(), screenWidth / 2 - (width / 2), 200, 40, BLACK);

	for (UpgradeButton* u : g->upgradeButtons)
	{
		u->Draw();

		//price
		std::string text = std::to_string(u->GetPrice()) + " C";
		int width = MeasureText(text.c_str(), 30);
		DrawText(text.c_str(), (int)u->GetPosition().x - width / 2, (int)u->GetPosition().y - 90, 30, (g->gameStats->totalCoins >= u->GetPrice()) ? GREEN : RED);

		//level
		text = std::to_string(g->gameStats->upgradeStates[u->GetUpgrade()].first);
		width = MeasureText(text.c_str(), 30);
		DrawText(text.c_str(), (int)u->GetPosition().x - (width / 2), (int)u->GetPosition().y + 70, 30, BLACK);
	}

	g->quitButton->Draw();
}

void UpgradeMenuHandler::HandleInput()
{
	if (this->game->quitButton->isReleased)
	{
		this->game->gameState = LevelSelectMenu;
		//this->game->quitButton->isClicked = false;
	}
}


