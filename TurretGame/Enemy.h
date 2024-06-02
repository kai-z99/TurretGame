#pragma once
#include "raylib.h"

class Enemy
{
public:
	virtual void Draw(); // default just draws its hitbox.
	virtual void Update(unsigned int frame); // defulat update is just pos and velocity

	void SetPosition(float x, float y);
	void SetVelocity(float x, float y);
	void SetHealth(float health);

	Rectangle GetHitbox() const;
	float GetHealth();
	bool IsActive();
	
protected:
	Vector2 position;
	Vector2 velocity;
	Rectangle hitbox;

	//TEXTURE PROPERTIES---------------
	Texture2D texture;
	int textureWidth;
	int textureHeight;
	Rectangle textureSourceRec;
	Rectangle textureDestRec;
	Vector2 textureOriginPoint;
	//---------------------------------

	bool isActive = true;
	int damage;
	float health;

	int animationState;
};