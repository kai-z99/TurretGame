#pragma once
#include "raylib.h"

class Bullet;
class TextureLoop;

class Enemy
{
public:
	virtual void Draw(); // default just draws its hitbox.
	void DrawCoinSplash();
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
	int GetCoinDropAmount() const;
	bool isActive = true;
	
protected:
	void DrawHealthbar(int yOffset, float barSize); //yOffset: how many px up from middle of image

	Vector2 position = {-300, -300};
	Vector2 velocity;
	Rectangle hitbox;

	TextureLoop* textureLoop;


	int id;
	int damage;
	float health;
	float maxHealth;
	float knockbackMultiplier;
	int knockbackFrames = 0;
	int coinDropAmount;

	int animationState;
};