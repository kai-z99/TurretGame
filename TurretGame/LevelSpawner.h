#pragma once
#include <vector>
#include <unordered_map>
#include "raylib.h"

class Game;
class Enemy;
class LevelHandler;
class BalloonBossEnemy;

class LevelSpawner
{
public:
	LevelSpawner(LevelHandler* levelHandler);

	void SetSpawnMap(int level);
	void HandleCurrentLevelSpawning();

	void SpawnSlimeBurst(Vector2 pos);

	bool IsFinishedSpawning();

private:
	//better as map
	void SpawnEnemyByID(int id);

	void HandleSpecialSpawning();
	void SpawnBirdShield(BalloonBossEnemy* host);
	
	LevelHandler* levelHandler;
	std::unordered_map<int, std::vector<unsigned int>> spawnMap; //id : frames to spawn

};