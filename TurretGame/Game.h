#pragma once
#include <vector>
#include <raylib.h>
#include <unordered_map>
#include "types.h"

class Turret;
class Bullet;
class AreaEffect;
class Enemy;
class Hotbar;
class VisualEffectsManager;
class LevelHandler;

class Game
{
public:
	Game();
	~Game();

	void Run();

	unsigned int frameCount;

	GameStats* gameStats;
	int currentLevel;

	std::vector<Enemy*> enemies;
	std::vector<Bullet*> bullets;
	std::vector<AreaEffect*> areaEffects;

	void CleanVectors();

private:
	void Initialize();
	void Draw();
	void DrawInLevel();
	//void DrawMenu etc
	// 
	//THIS SHOULD BE IN VISUAL EFFECTS MANAGER
	void DrawVisualEffects();


	void Update();
	//void UpdateMenu etc

	GameState gameState;
	void StartCurrentLevel();
	void ExitCurrentLevel();

	void HandleCollisions();
	void HandleBulletCollideEnemy(Enemy* e, Bullet* b);
	void HandleInput();
	void HandleEnemySpawning();

	void ActivateUsedAbilities();
	void CleanBulletVector();

	Turret* turret;
	Hotbar* hotbar;

	VisualEffectsManager* effectManager;

	LevelHandler* levelHandler;

	const int bulletLimit = 200; //how many bullets can be on the screen
	
	int inputMode; //0: standard, 1: bomb, 2 : ice
	Vector2 mousePos;
	

};