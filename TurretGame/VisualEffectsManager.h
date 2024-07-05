#pragma once
#include "raylib.h"
#include <vector>

class VisualEffect;
class Game;

class VisualEffectsManager
{
public:
	VisualEffectsManager(Game* g);
	~VisualEffectsManager();
	void DisplayCoinSplash(Vector2 pos, int amount);
	void DisplayExplosion(Vector2 pos);
	void DisplayFire(Vector2 pos, float scale);
	void DisplayIceSparkle(Vector2 pos, float scale);
	void DisplaySparkle(Vector2 pos, float scale);

	void UpdateAndDraw();

	void Clear();

	int lightningAlpha;

private:
	Game* game;
	std::vector<VisualEffect*> tasks; // animationtype, frames remaining
	void CleanTasks();

	void DrawBulletTrails();
	void DrawIceSheetParticles();
	void DrawEnemyBurning();
	void DrawLightning();

	const int taskLimit = 700;

};