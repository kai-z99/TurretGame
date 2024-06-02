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

	int GetID() const;
	Rectangle GetHitbox() const;
	Vector2 GetPosition() const;
	float GetHealth();
	int GetDamage() const;
	bool isActive = true;
	
protected:
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

	int animationState;
};