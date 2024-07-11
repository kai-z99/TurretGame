#pragma once
#include <vector>
#include <unordered_map>
#include "raylib.h"
#include "constants.h"

class Bullet;
class TurretLaser;
struct BulletCooldownInfo;

class Turret
{
public:
	Turret();
	~Turret();

	void Draw();
	void Update(unsigned int frame, int mouseX, int mouseY);

	void ShootBullet(std::vector<Bullet*>& bullets, int id); //TAKE BULLET ID AS PARAM TO SHOOT TYPES

	void SetBulletSpeedMultiplier(float multiplier);
	void SetBaseFirerate(float firerate);
	void SetFirerate(int id, float firerate);
	void SetPosition(int x, int y);

	void SetRapidFire(unsigned int frames);
	void SetLaserFrames(unsigned int frames);

	float GetCurrentBaseFirerate();
	float GetFirerate(int id);
	const std::unordered_map<int, BulletCooldownInfo*>& GetBulletCooldownMap();

	bool IsBulletUnlocked(int id);
	void UnlockBullet(int id);

	bool main = true; // main is the main turret only not sentry

	friend class UpgradeMenuHandler;
	friend class TurretLaser;

	TurretLaser* GetLaser();

	static int rapidFireDuration;
	static float rapidFirerateMultiplier;

protected:
	void UpdateAngle(int mouseX, int mouseY);

	Vector2 position = { 100.0f, (screenHeight / 2.0f) + (menuBoundaryY / 2.0f)};
	float angle;

	TurretLaser* laser;

	//TEXTURE PROPERTIES---------------
	Texture2D* texture;
	int textureWidth;
	int textureHeight;
	Rectangle textureSourceRec;
	Rectangle textureDestRec;
	Vector2 textureOriginPoint;
	//---------------------------------

	//GAME PROPERTIES------------------
	std::unordered_map<int, BulletCooldownInfo*> bulletCooldownMap; // bullet id : info
	float bulletSpeedMultiplier;

	float baseFirerate;
	float currentFirerate;
	float rapidFirerate;
	int rapidFireFrames;	
	int laserFrames;
};