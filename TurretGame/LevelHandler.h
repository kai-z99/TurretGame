#pragma once

class Game;
struct CurrentLevelStats;

class LevelHandler
{
public:
	LevelHandler(Game* game);

	void Update(unsigned int frame);

	void Draw();

	void InitializeCurrentLevel();
	void HandleCurrentLevelSpawning();
	void ExitCurrentLevel();

	CurrentLevelStats* currentLevelStats;

private:
	Game* game;
	unsigned int currentLevelFrameCount;

	void SpawnClassicEnemy(int id);
	
	void ActivateUsedAbilities();

	void DrawVisualEffects();

};