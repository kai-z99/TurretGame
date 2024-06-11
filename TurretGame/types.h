#pragma once
#include <unordered_map>

enum TurretAbility
{
	Rapidfire,
	SpecialRapidfire,
	placeholder,
	Explosive,
	Knockback,
	Burn,

};

enum GameState
{
	InLevel,
	UpgradeMenu,
	LevelSelectMenu,
	MainMenu,
};

enum StatusEffect
{
	Burning,
	Frozen,
	Chilled,
	Stunned,
	Poisoned,
};

struct BulletCooldownInfo
{
	bool shotThisFrame;
	bool canShoot;
	unsigned int lastShotFrame;
};


struct AbilityInfo
{
	int cooldown;
	int lastUsedFrame;
	//bool canUse;

	short maxCharges;
	short charges;
};


struct GameStats
{
	int health;
	int totalCoins;
	int coinsCollectedInLevel;

	std::unordered_map<TurretAbility, AbilityInfo> abilityStates; //ability : (currentcharges : maxcharges)



	//upgrades
};