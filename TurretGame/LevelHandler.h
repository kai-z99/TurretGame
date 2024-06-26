#pragma once
#include <vector>

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

	unsigned int currentLevelFrameCount;
	
	void ActivateUsedAbilities();
	void HandleCurrentLevelSpawning();
	void DrawVisualEffects();
	bool NoActiveEnemies();

	bool currentLevelComplete;
	bool currentLevelLose;
};