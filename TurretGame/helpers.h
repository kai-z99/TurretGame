#pragma once

float CalculateAngle(int x0, int y0, int x1, int y1);

struct BulletCooldownInfo
{
	bool shotThisFrame;
	bool canShoot;
	unsigned int lastShotFrame;
};