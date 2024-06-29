#pragma once
#include "raylib.h"

class Enemy;
class Turret;

class TurretLaser
{
public:
	TurretLaser(Turret* t);

	void Update(unsigned int frame);
	void Draw();

	bool isCollide(Enemy* e);

	bool isDamageFrame;
	bool isActive;
	
	static int duration;
	static int damage;

	static Color color;

private:

	float thickness;
	float angle;

	Vector2 p1;
	Vector2 p2;
	Turret* owner;

	const float length = 2000.0f;
};