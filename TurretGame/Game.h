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
class LevelSelectHandler;
class LevelButton;

class Game
{
public:
	Game();
	~Game();

	void Run();

	friend class LevelHandler;
	friend class CollisionHandler;
	friend class LevelSelectHandler;

private:
	void Initialize();

	GameState gameState;
	unsigned int frameCount;

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

	void PlayLevel(int level);

	void StartCurrentLevel();
	void ExitCurrentLevel();

	void CleanBulletVector();
	void ClearVectors();

	Turret* turret;
	Hotbar* hotbar;
	GameStats* gameStats;

	std::vector<Enemy*> enemies;
	std::vector<Bullet*> bullets;
	std::vector<AreaEffect*> areaEffects;

	std::vector<LevelButton*> levelButtons;
	
	VisualEffectsManager* effectManager;
	LevelHandler* levelHandler;
	CollisionHandler* collisionHandler;
	LevelSelectHandler* levelSelectHandler;

	int currentLevel;
	const int bulletLimit = 1000; //how many bullets can be on the screen
	const int enemyLimit = 800;
	const int AOELimit = 800;
	
	int inputMode; //0: standard, 1: bomb, 2 : ice
	Vector2 mousePos;
	

};