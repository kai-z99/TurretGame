#pragma once

class Game;
struct CurrentLevelStats;

class LevelHandler
{
public:
	LevelHandler(Game* game);

	void Update(unsigned int frame);

	void InitializeCurrentLevel();
	void HandleCurrentLevelSpawning();
	void ExitCurrentLevel();

	CurrentLevelStats* currentLevelStats;

private:
	Game* game;
	unsigned int currentLevelFrameCount;

	void SpawnClassicEnemy(int id);
	
};