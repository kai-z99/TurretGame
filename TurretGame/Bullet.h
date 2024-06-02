#pragma once
#include "Projectile.h"

class Enemy;

class Bullet : public Projectile
{
public:
	virtual void Draw() override; //default draw is a red circle; debug only
	virtual void Update() override; // default is pos and velocty update (same as projectile)
	bool EnemyCollided(Enemy* e);

	float GetBaseSpeed() const;
	float GetBaseDamage() const;
	int GetID() const;

	bool isActive = true;
	//bool IsActive();
	

protected:

	//TEXTURE PROPERTIES---------------
	Texture2D* texture;
	int textureWidth;
	int textureHeight;
	Rectangle textureSourceRec;
	Rectangle textureDestRec;
	Vector2 textureOriginPoint;
	//---------------------------------

	float baseDamage;
	float baseSpeed;
	float hitBoxRadius;
	int id; // 1: turret 2: 


};