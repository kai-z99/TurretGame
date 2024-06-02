#pragma once
#include "raylib.h"


class Projectile
{
public:
	virtual void Draw(); // default draw is a circle. ONLY FOR DEBUG
	virtual void Update(); // default is pos and velocty update

	void SetPosition(float x, float y);
	void SetVelocity(float x, float y);

protected:
	Vector2 position;
	Vector2 velocity;
};