#pragma once

#include <vector>

#include "Turret.h"

class Enemy;

class Sentry : public Turret
{
public:
	Sentry();
	
	void Update(unsigned int frame, int mouseX, int mouseY, std::vector<Enemy*>& enemies, std::vector<Bullet*>& bullets);

	void SetTargetMode(int mode);


private:
	Enemy* target;
	int targetMode; //0: close, 1: strong
};