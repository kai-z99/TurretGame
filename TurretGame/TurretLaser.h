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
	
	int GetDamage() const;


	bool isDamageFrame;
	bool isActive;
	
	//temp
	Color color = { 255,0,0,180 };
private:

	float thickness;
	float angle;

	int damage;

	Vector2 p1;
	Vector2 p2;
	Turret* owner;

	const float length = 2000.0f;
};