#pragma once
#include <vector>
#include <raylib.h>
#include <unordered_map>
#include "types.h"
#include <string>

class Turret;
class Sentry;
class Bullet;
class AreaEffect;
class Enemy;
class Hotbar;
class Decoration;

class VisualEffectsManager;
class LevelHandler;
class CollisionHandler;
class LevelSelectHandler;
class UpgradeMenuHandler;
class MainMenuHandler;
class SoundHandler;

class TextButton;
class LevelButton;
class UpgradeButton;



class Game
{
public:
	Game();
	~Game();

	void Run();

	friend class VisualEffectsManager;
	friend class CollisionHandler;
	friend class LevelHandler;
	friend class LevelSelectHandler;
	friend class UpgradeMenuHandler;
	friend class MainMenuHandler;
	friend class LevelSpawner;
	friend class SoundHandler;
	

private:
	void Initialize();

	GameState gameState;
	unsigned int frameCount;

	//----------------------------------------
	void Draw();

	void DrawInLevel();

	void DrawLevelSelectMenu();

	void DrawUpgradeMenu();

	void DrawMainMenu();
	//----------------------------------------
	void Update();

	void UpdateInLevel();

	void UpdateLevelSelectMenu();

	void UpdateUpgradeMenu();

	void UpdateMainMenu();
	//----------------------------------------
	void HandleInput();

	void HandleInputInLevel();

	void HandleInputLevelSelectMenu();

	void HandleInputUpgradeMenu();

	void HandleInputMainMenu();
	//-----------------------------------------


	void StartCurrentLevel();
	void ExitCurrentLevel();

	void CleanBulletVector();
	void ClearVectors();

	void DrawMousePos(); //debug

	void SetGameStatsToDefault();				  //called on game init
	void SetGameStatsToDatabaseValues();		  //called at game init and on upgrade (upgrade states) and on level completion (levels complete values)
	void SetDatabaseValuesToGameStats();

	void SetTurretsAndAbilitiesToUpgradeValues(); //called on level play

	//helpers for SetTurretsAndAbilitiesToUpgradeValues()
	void HandleBulletUpgrade(int bulletID, Turret* t, Sentry* s1, Sentry* s2);
	void SetAbilityStaticsToDefault();
	void HandleAbilityUpgrade(Upgrade upgrade);


	Turret* turret;
	Sentry* sentry1;
	Sentry* sentry2;
	Hotbar* hotbar;
	GameStats* gameStats;

	TextButton* tryAgainButton;
	TextButton* returnButton;
	TextButton* quitButton;
	TextButton* shopButton;
	TextButton* startButton;

	std::vector<Enemy*> enemies;
	std::vector<Bullet*> bullets;
	std::vector<AreaEffect*> areaEffects;
	std::vector<Vector2> lightningPoints;
	
	std::vector<Decoration*> decorations;
	std::vector<LevelButton*> levelButtons;
	std::vector<UpgradeButton*> upgradeButtons;
	
	VisualEffectsManager* effectManager;
	LevelHandler* levelHandler;
	CollisionHandler* collisionHandler;
	LevelSelectHandler* levelSelectHandler;
	UpgradeMenuHandler* upgradeMenuHandler;
	MainMenuHandler* mainMenuHandler;
	SoundHandler* soundHandler;

	int currentLevel;
	const int bulletLimit = 1000; //how many bullets can be on the screen
	const int enemyLimit = 800;
	const int AOELimit = 800;
	
	int inputMode; //0: standard, 1: bomb, 2 : ice
	Vector2 mousePos;

	std::string userAppDataPath;

};