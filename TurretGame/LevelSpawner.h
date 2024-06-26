#pragma once
#include <vector>
#include <unordered_map>
#include "raylib.h"

class Game;
class Enemy;
class LevelHandler;

class LevelSpawner
{
public:
	LevelSpawner(LevelHandler* levelHandler);

	void SetSpawnMap(int level);
	void HandleCurrentLevelSpawning();

	bool IsFinishedSpawning();

private:
	//better as map
	void SpawnEnemyByID(int id);
	
	
	LevelHandler* levelHandler;
	std::unordered_map<int, std::vector<unsigned int>> spawnMap; //id : frames to spawn

};