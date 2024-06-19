#pragma once
#include <unordered_map>

enum TurretAbility
{
	Rapidfire,
	SpecialRapidfire,
	Ice,
	Explosive,
	Shock,
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

	short maxCharges;
	short charges;
};


struct GameStats
{
	int totalCoins;
	
	//UPGRADES

	//abilities
	std::unordered_map<TurretAbility, AbilityInfo> initialAbilityValues;

};

struct CurrentLevelStats
{
	int health;
	int coinsCollected;
	std::unordered_map<TurretAbility, AbilityInfo> abilityStates; //ability : (currentcharges : maxcharges)
};