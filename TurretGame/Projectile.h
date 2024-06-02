#pragma once
#include "raylib.h"


class Projectile
{
public:
	virtual void Draw(); //temp should be virtual
	void Update();

	void SetPosition(float x, float y);
	void SetVelocity(float x, float y);

protected:
	Vector2 position;
	Vector2 velocity;
};