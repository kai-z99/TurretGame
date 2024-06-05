#pragma once
#include "raylib.h"


class Projectile
{
public:
	virtual void Draw(); // default draw is a circle. ONLY FOR DEBUG
	virtual void Update(unsigned int frame); // default is pos and velocty update

	void SetPosition(float x, float y);
	void SetVelocity(float x, float y);

protected:
	Vector2 position = {-300, -300}; //default position is off site
	Vector2 velocity;
};