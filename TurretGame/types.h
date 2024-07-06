#pragma once
#include <unordered_map>

enum TurretAbility
{
	Rapidfire = 0,
	Laser,
	Ice,
	Explosive,
	Clone,
	Burn,
};

enum GameState
{
	InLevel = 0,
	UpgradeMenu,
	LevelSelectMenu,
	MainMenu,
};

enum StatusEffect
{
	Burning = 0,
	Frozen,
	Chilled,
	Stunned,
	Poisoned,
};

enum Upgrade
{
	TurretBulletU = 0,
	ShockwaveBulletU,
	FireBulletU,
	SniperBulletU,
	LightningBulletU,
	RapidfireU,
	LaserU,
	IceU,
	ExplosiveU,
	SentryU,
};

struct BulletCooldownInfo
{
	bool unlocked;
	bool shotThisFrame;
	bool canShoot;
	unsigned int lastShotFrame;
	float firerate;
};


struct AbilityInfo
{
	int cooldown;
	int lastUsedFrame;

	short maxCharges;
	short charges;
};


struct UpgradeInfo
{
	int level;
	int price;
};

struct GameStats
{
	int totalCoins;
	int initialHealth;
	//UPGRADES

	//abilities
	std::unordered_map<TurretAbility, AbilityInfo> initialAbilityValues;
	std::unordered_map<Upgrade, UpgradeInfo> upgradeStates;

};

struct CurrentLevelStats
{
	int health;
	int coinsCollected;
	std::unordered_map<TurretAbility, AbilityInfo> abilityStates; //ability : (currentcharges : maxcharges)
};