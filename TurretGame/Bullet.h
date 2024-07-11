#pragma once
#include "Projectile.h"

class Enemy;
class Turret;

class Bullet : public Projectile
{
public:
	virtual void Draw() override; //default draw is a red circle; debug only
	virtual void Update(unsigned int frame) override; // default is pos and velocty update (same as projectile)
	bool EnemyCollided(Enemy* e);

	float GetBaseSpeed() const;
	float GetBaseDamage() const;
	int GetBaseKnockbackDuration() const;
	int GetID() const;
	Turret* GetOwner() const;

	bool isActive = true;

	

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
	int baseKnockbackDuration;
	float hitBoxRadius;
	float angle;

	int id; // 1: turret 2: shockwave

	Turret* owner;


};