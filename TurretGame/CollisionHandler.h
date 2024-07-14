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

	void HandleBulletToEnemy(Bullet* b, Enemy* e);
	void HandleAOEToEnemies(AreaEffect* a);
	void HandleLaserToEnemy(TurretLaser* laser, Enemy* e);


private:
	Game* game;

	void ApplyLightning(Enemy* e, int length);
};