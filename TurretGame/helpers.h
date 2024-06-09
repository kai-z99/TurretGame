#pragma once
#include <unordered_map>
#include "types.h"

float CalculateAngle(int x0, int y0, int x1, int y1); // based on 2 points, for position
float CalculateAngle(int x, int y); //based on just x and y;

struct BulletCooldownInfo
{
	bool shotThisFrame;  
	bool canShoot;
	unsigned int lastShotFrame;
};

struct GameStats
{
	int health;
	int totalCoins;
	int coinsCollectedInLevel;

	std::unordered_map<TurretAbility, std::pair<int, int>> abilityCharges; //ability : (currentcharges : maxcharges)


	//upgrades
};