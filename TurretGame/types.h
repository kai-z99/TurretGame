#pragma once
#include <unordered_map>

enum TurretAbility
{
	Rapidfire = 0,
	Laser,
	Ice,
	Explosive,
	Clone,
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
	BombBulletU,
	RapidfireU,
	LaserU,
	IceU,
	ExplosiveU,
	CloneU,
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

struct GameStats
{
	int totalCoins;
	int initialHealth;
	//UPGRADES

	//abilities
	std::unordered_map<Upgrade, std::pair<int,int>> upgradeStates; // Upgrade , {level,price}

};

struct CurrentLevelStats
{
	int health;
	std::unordered_map<TurretAbility, AbilityInfo> abilityStates; //ability : (currentcharges : maxcharges)
};