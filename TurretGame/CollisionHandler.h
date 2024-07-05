#pragma once

class Game;
class Enemy;
class Bullet;
class AreaEffect;
class TurretLaser;

class CollisionHandler
{
public:
	CollisionHandler(Game* game);

	void HandleEnemyCollisions();


private:
	Game* game;

	void HandleBulletToEnemy(Bullet* b, Enemy* e);
	void HandleAOEToEnemies(AreaEffect* a);
	void HandleLaserToEnemies(TurretLaser* laser);

	void ApplyLightning(Enemy* e, int length);
};