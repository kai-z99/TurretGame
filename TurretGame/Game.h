#pragma once
#include <vector>
#include <raylib.h>

class Turret;
class Bullet;
class Enemy;


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

	int playerHealth;

	Turret* turret;

	const int bulletLimit = 300;
	std::vector<Bullet*> bullets;
	std::vector<Enemy*> enemies;

	Vector2 mousePos;
	unsigned int frameCount;
};