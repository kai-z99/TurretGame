#include "UpgradeMenuHandler.h"
#include <iostream>
#include <string>

#include "constants.h"
#include "types.h"

#include "Game.h"
#include "UpgradeButton.h"
#include "Turret.h"

#include "textures.h"

UpgradeMenuHandler::UpgradeMenuHandler(Game* g)
{
	this->game = g;

	for (int i = 0; i <= 7; i++)
	{
		this->game->upgradeButtons.push_back(new UpgradeButton(100 * i, 500, (Upgrade)i));
		this->game->upgradeButtons[i]->SetPrice(this->game->gameStats->upgradeStates[Upgrade(i)].price);
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
			g->gameStats->totalCoins -= u->GetPrice(); //spend coins

			this->HandleUpgrade(u->GetUpgrade()); //do what the upgrade does

			//add a levl to that upgrade
			g->gameStats->upgradeStates[u->GetUpgrade()].level += 1;

			//increase the price of it
			g->gameStats->upgradeStates[u->GetUpgrade()].price += (int)(10 + g->gameStats->upgradeStates[u->GetUpgrade()].price * 0.2);
			g->upgradeButtons[u->GetUpgrade()]->SetPrice(this->game->gameStats->upgradeStates[u->GetUpgrade()].price);

		}
	}
}

void UpgradeMenuHandler::HandleUpgrade(Upgrade u)
{
	Game* g = this->game;
	Turret* t = g->turret;

	switch (u)
	{
	case TurretBulletU:
		t->SetFirerate(1, t->GetFirerate(1) + 0.2f);
		break;

	case ShockwaveBulletU: //id for shockwave bullet is 2
		if (t->IsBulletUnlocked(2)) t->SetFirerate(2, t->GetFirerate(2) + 0.2f);
		else (t->UnlockBullet(2));
		break;

	case FireBulletU://id for shockwave bullet is 3
		if (t->IsBulletUnlocked(3)) t->SetFirerate(3, t->GetFirerate(3) + 0.2f);
		else (t->UnlockBullet(3));
		break;

	case SniperBulletU:
		if (t->IsBulletUnlocked(4)) t->SetFirerate(4, t->GetFirerate(4) + 0.2f);
		else (t->UnlockBullet(4));
		break;


	//TEMP, do more than just increase charges
	case RapidfireU:
		g->gameStats->initialAbilityValues[Rapidfire].charges += 1;
		g->gameStats->initialAbilityValues[Rapidfire].maxCharges += 1;
		break;

	case SpecialRapidfireU:
		g->gameStats->initialAbilityValues[SpecialRapidfire].charges += 1;
		g->gameStats->initialAbilityValues[SpecialRapidfire].maxCharges += 1;
		break;

	//TEMP
	case IceU:
		g->gameStats->initialAbilityValues[Ice].charges += 1;
		g->gameStats->initialAbilityValues[Ice].maxCharges += 1;
		break;

	//TEMP
	case ExplosiveU:
		g->gameStats->initialAbilityValues[Explosive].charges += 1;
		g->gameStats->initialAbilityValues[Explosive].maxCharges += 1;
		break;

	default:
		std::cout << "Upgrade does not exist.";
		break;
	}
}

void UpgradeMenuHandler::Draw()
{
	Game* g = this->game;
	DrawText("Upgrade!", screenWidth / 2 - 100, 100, 50, RED);
	DrawText(std::to_string(g->gameStats->totalCoins).c_str(), 10, 10, 30, BLUE);

	for (UpgradeButton* u : g->upgradeButtons)
	{
		u->Draw();
		DrawText(std::to_string(g->gameStats->upgradeStates[u->GetUpgrade()].level).c_str(), (int)u->GetPosition().x, (int)u->GetPosition().y + 30, 30, RED);
	}
}

void UpgradeMenuHandler::HandleInput()
{
	if (IsKeyPressed(KEY_UP))
	{
		this->game->gameState = LevelSelectMenu;
	}
}


