#pragma once

float CalculateAngle(int x0, int y0, int x1, int y1); // based on 2 points, for position
float CalculateAngle(int x, int y); //based on just x and y;

struct BulletCooldownInfo
{
	bool shotThisFrame;  
	bool canShoot;
	unsigned int lastShotFrame;
};