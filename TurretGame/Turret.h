#pragma once
#include <vector>
#include "raylib.h"
#include "constants.h"

class Bullet;

class Turret
{
public:
	Turret();
	void Draw();
	void Update(unsigned int frame, int mouseX, int mouseY);

	void ShootProjectile(std::vector<Bullet*>& projectiles);

	void SetBulletSpeedMultiplier(float multiplier);
	void SetFirerate(float firerate);

	float GetFirerate();
	unsigned int GetLastShotFrame();
	bool GetCanShoot();

private:
	void UpdateAngle(int mouseX, int mouseY);

	Vector2 position = { 100.0f, (screenHeight / 2.0f) + (menuBoundaryY / 2.0f)};
	float angle;

	//TEXTURE PROPERTIES---------------
	Texture2D* texture;
	int textureWidth;
	int textureHeight;
	Rectangle textureSourceRec;
	Rectangle textureDestRec;
	Vector2 textureOriginPoint;
	//---------------------------------

	//GAME PROPERTIES------------------
	bool canShoot;
	bool shotThisFrame;
	int lastShotFrame;

	float bulletSpeedMultiplier;

	float firerate;
};