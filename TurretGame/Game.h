#pragma once
#include <vector>
#include <raylib.h>
#include <unordered_map>
#include "types.h"

class Turret;
class Bullet;
class Enemy;
class Hotbar;
class VisualEffectsManager;



class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	void Initialize();
	void Draw();
	void DrawVisualEffects();
	void Update();

	void HandleCollisions();
	void HandleBulletCollideEnemy(Enemy* e, Bullet* b);
	void HandleInput();
	void HandleEnemySpawning();

	void ActivateUsedAbilities();
	void CleanBulletVector();

	Turret* turret;
	Hotbar* hotbar;
	GameStats* gameStats;
	VisualEffectsManager* effectManager;

	const int bulletLimit = 200; //how many bullets can be on the screen
	std::vector<Bullet*> bullets;
	std::vector<Enemy*> enemies;
	

	Vector2 mousePos;
	unsigned int frameCount;

	//DATA BASE
	 std::unordered_map<TurretAbility, AbilityInfo> abilityDB;
};