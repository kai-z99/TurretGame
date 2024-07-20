#pragma once
#include <unordered_map>
#include "types.h"
#include "constants.h"



//UPGRADES

namespace UpgradeDatabase
{
	extern const std::unordered_map<Upgrade, std::pair<int, int>> initialUpgradeInfo;
	extern std::unordered_map<Upgrade, std::pair<int, int>> currentUpgradeInfo; //upgrade, {level, cost}

	extern const std::unordered_map<int, float> bulletFirerateIncreaseAmounts; //bulletid , increase amount

	extern int totalCoins;
}

//ABILITIES
namespace AbilityDatabase
{
	extern const std::unordered_map<TurretAbility, int> abilityCooldowns;
	std::unordered_map<TurretAbility, short> GetRoundStartAbilityCharges();


}





void LoadDataFromFile();

