#pragma once
#include <vector>
#include <unordered_map>
#include "raylib.h"
#include "constants.h"

class Bullet;
struct BulletCooldownInfo;

class Turret
{
public:
	Turret();
	void Draw();
	void Update(unsigned int frame, int mouseX, int mouseY);

	void ShootBullet(std::vector<Bullet*>& bullets, int id); //TAKE BULLET ID AS PARAM TO SHOOT TYPES

	void SetBulletSpeedMultiplier(float multiplier);
	void SetBaseFirerate(float firerate);
	void SetBaseSpecialFirerate(float firerate);
	void SetRapidFire(unsigned int frames);
	void SetSpecialRapidfire(unsigned int frames);
	

	float GetCurrentFirerate();
	const std::unordered_map<int, BulletCooldownInfo*>& GetBulletCooldownMap();

	

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
	std::unordered_map<int, BulletCooldownInfo*> bulletCooldownMap; // bullet id : info
	float bulletSpeedMultiplier;

	float baseFirerate;
	float currentFirerate;
	float rapidFirerate;
	int rapidFireFrames;

	float baseSpecialFirerate;
	float currentSpecialFirerate; //firerate of speical bullets
	float rapidSpecialFirerate;
	int specialRapidfireFrames;
	

	
};