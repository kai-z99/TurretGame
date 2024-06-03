#pragma once
#include "raylib.h"

class Bullet;

class Enemy
{
public:
	virtual void Draw(); // default just draws its hitbox.
	virtual void Update(unsigned int frame); // defulat update is just pos and velocity

	void SetPosition(float x, float y);
	void SetVelocity(float x, float y);
	void SetHealth(float health);
	void ApplyKnockback(Bullet* b);

	int GetID() const;
	Rectangle GetHitbox() const;
	Vector2 GetPosition() const;
	float GetHealth();
	float GetMaxHealth();
	int GetDamage() const;
	bool isActive = true;
	
protected:
	void DrawHealthbar(int yOffset, float barSize); //yOffset: how many px up from middle of image

	Vector2 position = {-300, -300};
	Vector2 velocity;
	Rectangle hitbox;


	//TEXTURE PROPERTIES---------------
	Texture2D* texture;
	int textureWidth;
	int textureHeight;
	Rectangle textureSourceRec;
	Rectangle textureDestRec;
	Vector2 textureOriginPoint;
	//---------------------------------

	int id;
	int damage;
	float health;
	float maxHealth;
	float knockbackMultiplier;
	int knockbackFrames = 0;

	int animationState;
};