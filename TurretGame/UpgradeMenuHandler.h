#pragma once
#include "types.h"

class Game;
class UpgradeButton;

class UpgradeMenuHandler
{
public:
	UpgradeMenuHandler(Game* g);

	void Update();
	void Draw();
	void HandleInput();

private:
	Game* game;
	//void HandleUpgrade(Upgrade u);

	//void HandleBulletUpgrade(int bulletID);
	//void HandleAbilityUpgrade(Upgrade upgrade);

	//float GetFirerateIncreaseAmountByID(int id);
};