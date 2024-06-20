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
class CollisionHandler;

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

	VisualEffectsManager* effectManager;

	void ClearVectors();

private:
	void Initialize();
	GameState gameState;

	//----------------------------------------
	void Draw();

	void DrawInLevel();
	void DrawVisualEffects();

	void DrawLevelSelectMenu();
	//----------------------------------------
	void Update();

	void UpdateInLevel();
	void HandleCollisions();

	void UpdateLevelSelectMenu();
	//----------------------------------------
	void HandleInput();

	void HandleInputInLevel();
	void HandleInputLevelSelectMenu();
	//-----------------------------------------

	
	void StartCurrentLevel();
	void ExitCurrentLevel();

	void HandleEnemySpawning();

	void ActivateUsedAbilities();
	void CleanBulletVector();

	Turret* turret;
	Hotbar* hotbar;

	LevelHandler* levelHandler;
	CollisionHandler* collisionHandler;

	const int bulletLimit = 1000; //how many bullets can be on the screen
	const int enemyLimit = 800;
	const int AOELimit = 800;
	
	int inputMode; //0: standard, 1: bomb, 2 : ice
	Vector2 mousePos;
	

};