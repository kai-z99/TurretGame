#pragma once
#include <vector>
#include "raylib.h"

class Game;
class Enemy;
class LevelSpawner;
struct CurrentLevelStats;

class LevelHandler
{
public:
	LevelHandler(Game* game);

	void Update(unsigned int frame);

	void Draw();

	void HandleInput();

	void InitializeCurrentLevel();
	void DeInitializeCurrentLevel();

	CurrentLevelStats* currentLevelStats;

	friend class LevelSpawner;

private:
	Game* game;
	LevelSpawner* levelSpawner;
	std::vector<Enemy*>* enemiesRef;

	Color redScreen;
	unsigned int currentLevelFrameCount;
	
	void ActivateUsedAbilities();
	void HandleCurrentLevelSpawning();
	bool NoActiveEnemies();

	void DrawCurrentLevelBackground();

	bool currentLevelComplete;
	bool currentLevelLose;

	int cooldownWarningFrames;
	int chargeWarningFrames;

	int sentryFrames;
};