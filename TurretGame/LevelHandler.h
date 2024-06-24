#pragma once
#include <vector>

class Game;
class Enemy;
class LevelBuilder;
struct CurrentLevelStats;

class LevelHandler
{
public:
	LevelHandler(Game* game);

	void Update(unsigned int frame);

	void Draw();

	void HandleInput();

	void InitializeCurrentLevel();
	void HandleCurrentLevelSpawning();
	void ExitCurrentLevel();

	CurrentLevelStats* currentLevelStats;

	friend class LevelBuilder;

private:
	Game* game;
	LevelBuilder* levelBuilder;
	std::vector<Enemy*>* enemiesRef;

	unsigned int currentLevelFrameCount;
	
	void ActivateUsedAbilities();

	void DrawVisualEffects();

};