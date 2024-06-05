#pragma once
#include <vector>
#include <raylib.h>

class Turret;
class Bullet;
class Enemy;
class Hotbar;
class VisualEffectsManager;

struct GameStats;

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	void Initialize();
	void Draw();
	void Update();

	void HandleCollisions();
	void HandleInput();
	void HandleEnemySpawning();

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
};