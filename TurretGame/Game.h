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


	void ClearVectors();

	friend class LevelHandler;
	friend class CollisionHandler;

private:
	void Initialize();
	GameState gameState;

	//----------------------------------------
	void Draw();

	void DrawInLevel();

	void DrawLevelSelectMenu();
	//----------------------------------------
	void Update();

	void UpdateInLevel();

	void UpdateLevelSelectMenu();
	//----------------------------------------
	void HandleInput();

	void HandleInputInLevel();

	void HandleInputLevelSelectMenu();
	//-----------------------------------------

	void StartCurrentLevel();
	void ExitCurrentLevel();

	void CleanBulletVector();

	Turret* turret;
	Hotbar* hotbar;

	std::vector<Enemy*> enemies;
	std::vector<Bullet*> bullets;
	std::vector<AreaEffect*> areaEffects;
	
	VisualEffectsManager* effectManager;
	LevelHandler* levelHandler;
	CollisionHandler* collisionHandler;

	const int bulletLimit = 1000; //how many bullets can be on the screen
	const int enemyLimit = 800;
	const int AOELimit = 800;
	
	int inputMode; //0: standard, 1: bomb, 2 : ice
	Vector2 mousePos;
	

};