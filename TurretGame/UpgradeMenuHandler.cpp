#include "UpgradeMenuHandler.h"
#include <iostream>
#include <string>

#include "constants.h"
#include "types.h"
#include "helpers.h"

#include "Game.h"
#include "UpgradeButton.h"
#include "Turret.h"
#include "Sentry.h"
#include "TurretLaser.h"
#include "IceSheet.h"
#include "BombExplosion.h"

#include "textures.h"

UpgradeMenuHandler::UpgradeMenuHandler(Game* g)
{
	this->game = g;

	for (int i = 0; i <= 10; i++)
	{
		this->game->upgradeButtons.push_back(new UpgradeButton(130 * i + 200, 500, (Upgrade)i));
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
		this->HandleBulletUpgrade(1);
		break;

	case ShockwaveBulletU: //id for shockwave bullet is 2
		this->HandleBulletUpgrade(2);
		break;

	case FireBulletU://id for shockwave bullet is 3
		this->HandleBulletUpgrade(3);
		break;

	case SniperBulletU:
		this->HandleBulletUpgrade(4);
		break;

	case LightningBulletU:
		this->HandleBulletUpgrade(5);
		break;

	case BombBulletU:
		this->HandleBulletUpgrade(6);
		break;

	case RapidfireU:
		//increase a chrage every 4 levels
		this->HandleAbilityUpgrade(u);
		Turret::rapidFirerateMultiplier += 0.15f;

		break;

	case LaserU:
		this->HandleAbilityUpgrade(u);

		if (TurretLaser::duration >= 400)
		{
			TurretLaser::duration = 100;
			TurretLaser::damage += 15.0f;
			TurretLaser::color = RotateColorChannels(TurretLaser::color);
		}

		TurretLaser::duration += 100;

		break;

	//TEMP
	case IceU:
		//increase a chrage every 4 levels
		this->HandleAbilityUpgrade(u);

		IceSheet::width += 15;
		IceSheet::height += 10;
		IceSheet::duration += 15;
		IceSheet::intensity += 10;
		break;

	//TEMP
	case ExplosiveU:
		this->HandleAbilityUpgrade(u);

		BombExplosion::radius += 10.0f;
		BombExplosion::damage += 50.0f;
		BombExplosion::knockbackFrames += 3;
		break;
	
	case CloneU:
		this->HandleAbilityUpgrade(u);

		Sentry::damageMultiplier += 0.1f;
		Sentry::duration += 20;
		break;


	default:
		std::cout << "Upgrade does not exist.";
		break;
	}
}

void UpgradeMenuHandler::HandleBulletUpgrade(int bulletID)
{
	Game* g = this->game;
	Turret* t = g->turret;

	if (t->IsBulletUnlocked(bulletID)) t->SetFirerate(bulletID, t->GetFirerate(bulletID) + 0.2f);
	else (t->UnlockBullet(bulletID));

	Sentry* s1 = this->game->sentry1;
	Sentry* s2 = this->game->sentry2;

	//sentries
	if (s1->IsBulletUnlocked(bulletID)) s1->SetFirerate(bulletID, s1->GetFirerate(bulletID) + 0.1f);
	else (s1->UnlockBullet(bulletID));

	if (s2->IsBulletUnlocked(bulletID)) s2->SetFirerate(bulletID, s2->GetFirerate(bulletID) + 0.1f);
	else (s2->UnlockBullet(bulletID));
}

void UpgradeMenuHandler::HandleAbilityUpgrade(Upgrade upgrade)
{
	Game* g = this->game;

	TurretAbility ability;

	switch (upgrade)
	{
	case RapidfireU:
		ability = Rapidfire;
		break;

	case LaserU:
		ability = Laser;
		break;

	case IceU:
		ability = Ice;
		break;

	case ExplosiveU:
		ability = Explosive;
		break;

	case CloneU:
		ability = Clone;
		break;
	}

	if (g->gameStats->upgradeStates[upgrade].level % 4 == 0)
	{
		g->gameStats->initialAbilityValues[ability].charges += 1;
		g->gameStats->initialAbilityValues[ability].maxCharges += 1;
	}
}

void UpgradeMenuHandler::Draw()
{
	Game* g = this->game;
	DrawText("Upgrade!", screenWidth / 2 - 100, 100, 50, RED);

	std::string text = std::to_string(g->gameStats->totalCoins) + " C";
	DrawText(text.c_str(), 10, 10, 30, BLACK);

	for (UpgradeButton* u : g->upgradeButtons)
	{
		u->Draw();

		//price
		std::string text = std::to_string(u->GetPrice()) + " C";
		int width = MeasureText(text.c_str(), 30);
		DrawText(text.c_str(), (int)u->GetPosition().x - width / 2, (int)u->GetPosition().y - 90, 30, (g->gameStats->totalCoins >= u->GetPrice()) ? GREEN : RED);

		//level
		text = std::to_string(g->gameStats->upgradeStates[u->GetUpgrade()].level);
		width = MeasureText(text.c_str(), 30);
		DrawText(text.c_str(), (int)u->GetPosition().x - (width / 2), (int)u->GetPosition().y + 70, 30, BLACK);
	}
}

void UpgradeMenuHandler::HandleInput()
{
	if (IsKeyPressed(KEY_UP))
	{
		this->game->gameState = LevelSelectMenu;
	}
}


