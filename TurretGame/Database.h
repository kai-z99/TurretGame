#pragma once
#include <unordered_map>
#include "types.h"
#include "constants.h"

#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

//UPGRADES

namespace UpgradeDatabase
{
	extern const std::unordered_map<Upgrade, std::pair<int, int>> INITIAL_UPGRADE_INFO;
	extern std::unordered_map<Upgrade, std::pair<int, int>> currentUpgradeInfo; //upgrade, {level, cost}

	extern const std::unordered_map<int, float> BULLET_FIRERATE_INCREASE_AMOUNTS; //bulletid , increase amount

	extern const int INITIAL_COINS;
	extern const int INITIAL_STARTING_HEALTH;

	extern int totalCoins;
	extern int startingHealth;
}

//ABILITIES
namespace AbilityDatabase
{
	extern const std::unordered_map<TurretAbility, int> ABILITY_COOLDOWNS;
}



namespace DBFunctions
{
	void LoadDatabaseFromFile(const char* filename);
	void SaveDatabaseToFile(const char* filename);

	std::unordered_map<TurretAbility, short> GetRoundStartAbilityCharges();
}



