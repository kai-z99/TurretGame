#pragma once
#include "raylib.h"
#include <unordered_map>
#include "types.h"

class Bullet;
class TextureLoop;

class Enemy
{
public:
	Enemy();
	~Enemy();
	virtual void Draw(); // default just draws its hitbox.
	virtual void Update(unsigned int frame); // defulat update is just pos and velocity, and does status effects

	void SetPosition(float x, float y);
	void SetCurrentVelocity(float x, float y);
	void SetHealth(float health);
	void ApplyKnockback(Bullet* b);
	void ApplyKnockback(int frames);
	void ApplyStatusEffect(StatusEffect effect, int frames);

	//constant?
	std::unordered_map<StatusEffect, int>& GetStatusEffects();

	int GetID() const;
	Rectangle GetHitbox() const;
	Vector2 GetPosition() const;
	Vector2 GetBaseVelocity() const;
	float GetHealth();
	float GetMaxHealth();
	int GetDamage() const;
	int GetCoinDropAmount() const;
	bool isActive = true;
	
protected:
	void DrawHealthbar(int yOffset, float barSize); //yOffset: how many px up from middle of image

	Vector2 position = {-300, -300};
	Vector2 currentVelocity;
	Vector2 baseVelocity;
	Rectangle hitbox;

	TextureLoop* textureLoop;
	Color tint = WHITE;

	int id;
	int damage;
	float health;
	float maxHealth;
	float knockbackMultiplier;
	int knockbackFrames = 0;
	int coinDropAmount;

	std::unordered_map<StatusEffect, int> statusEffects; // effect : frames;

	int animationState;
};