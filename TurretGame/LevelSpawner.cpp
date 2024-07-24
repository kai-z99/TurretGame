#include "LevelSpawner.h"
#include <iostream>
#include "constants.h"
#include "helpers.h"

#include "Game.h"
#include "LevelHandler.h"

#include "Enemy.h"
#include "SoldierEnemy.h"
#include "KoopaEnemy.h"
#include "RedKoopaEnemy.h"
#include "WolfEnemy.h"
#include "BatEnemy.h"
#include "SlimeEnemy.h"
#include "BalloonBossEnemy.h"
#include "BalloonBulletEnemy.h"
#include "SpinBirdEnemy.h"
#include "BeetleEnemy.h"
#include "BlackSoldierEnemy.h"
#include "WizardBossEnemyP1.h"
#include "WizardBulletEnemy.h"
#include "WizardFireEnemy.h"

LevelSpawner::LevelSpawner(LevelHandler* levelHandler)
{
	this->levelHandler = levelHandler;
}

void LevelSpawner::HandleCurrentLevelSpawning()
{
	//for every enemy id
	for (const auto& [enemyID,framesToSpawn] : this->spawnMap)
	{
		//for each frame they should spawn
		for (const int& frame : framesToSpawn)
		{
			//if thats the current frame
			if (levelHandler->currentLevelFrameCount == frame)
			{
				this->SpawnEnemyByID(enemyID);
			}
		}
	}
	
	this->HandleSpecialSpawning();
}

void LevelSpawner::HandleSpecialSpawning()
{
	switch (this->levelHandler->game->currentLevel)
	{
	//balloon boss
	case 6:
	{
		BalloonBossEnemy* boss = dynamic_cast<BalloonBossEnemy*>((*this->levelHandler->enemiesRef)[0]);

		//throw bullets
		if (boss->isActive && boss->isShootFrame)
		{
			BalloonBulletEnemy* e = new BalloonBulletEnemy();
			e->SetPosition(boss->GetPosition().x, boss->GetPosition().y + 60.0f);
			if (boss->GetPhase() == 3) e->SetFast();
			this->levelHandler->enemiesRef->push_back(e);
		}

		//spawn bird shield
		if (boss->isActive && boss->GetPhase() == 2 && !boss->spawnedShield)
		{
			this->SpawnBirdShield(boss);
			boss->spawnedShield = true;
		}
		break;
	}
	//wizard boss
	case 12:
	{
		WizardBossEnemyP1* boss = dynamic_cast<WizardBossEnemyP1*>((*this->levelHandler->enemiesRef)[0]);

		//spawn bullets
		if (boss->isActive && boss->isShootFrame)
		{
			WizardBulletEnemy* e = new WizardBulletEnemy();

			std::pair<Vector2, Vector2> spawnInfo = boss->GetBulletSpawnInstructions();
			Vector2 pos = spawnInfo.first;
			Vector2 vel = spawnInfo.second;

			e->SetPosition(pos.x, pos.y);
			e->SetBaseVelocity(vel.x, vel.y);
			this->levelHandler->enemiesRef->push_back(e);

			//spawn fire if in phase 2
			if (boss->GetPhase() == 2 && boss->fireWithBullet)
			{
				WizardFireEnemy* w = new WizardFireEnemy();
				w->SetPosition(GetRandomFloat(deathBoundaryX + 80, screenWidth - 380), screenHeight + 100);
				this->levelHandler->enemiesRef->push_back(w);
			}
			
		}

		else if (boss->isActive && boss->isBurstFrame)
		{
			this->SpawnWizardBurst(boss);
		}

		//make bullets blue if touch flame
		if (boss->GetPhase() == 2)
		{
			for (Enemy* fire : *this->levelHandler->enemiesRef)
			{
				if (fire->isActive && fire->GetID() == 13 && dynamic_cast<WizardFireEnemy*>(fire)->GetLocalFramecount() > 1) //wizard fire enemy. check if local frame is 1 because at frame 0/1 its position is at {-300,300}
				{
					for (Enemy* bullet : *this->levelHandler->enemiesRef)
					{
						if (bullet->GetID() == 12) //wizard bullet enemy
						{
							if (CheckCollisionRecs(fire->GetHitbox(), bullet->GetHitbox()))
							{
								dynamic_cast<WizardBulletEnemy*>(bullet)->ignited = true;
							}
						}
					}
				}
			}
		}

		break;
	}
	}

	std::vector<Vector2> slimePositions = {};
	//SLIME SPLITTING
	for (Enemy* e : this->levelHandler->game->enemies)
	{
		if (e->GetID() == 6)
		{
			SlimeEnemy* slime = dynamic_cast<SlimeEnemy*>(e);

			if (!slime->small && !slime->splitted && slime->GetHealth() <= 0)
			{
				slime->splitted = true;
				slimePositions.push_back(slime->GetPosition());
				
			}		
		}
	}

	for (const Vector2& pos : slimePositions)
	{
		this->SpawnSlimeBurst(pos);
	}

	slimePositions.clear();
}

//for balloon boss
void LevelSpawner::SpawnBirdShield(BalloonBossEnemy* host)
{
	if (this->levelHandler->game->currentLevel == 6)
	{
		if (host->GetPhase() == 2)
		{
			//set the spinners
			SpinBirdEnemy* s1 = new SpinBirdEnemy(dynamic_cast<BalloonBossEnemy*>(host));
			s1->SetPosition(host->GetPosition().x - 300, host->GetPosition().y);

			SpinBirdEnemy* s2 = new SpinBirdEnemy(dynamic_cast<BalloonBossEnemy*>(host));
			s2->SetPosition(host->GetPosition().x + 300, host->GetPosition().y);

			SpinBirdEnemy* s3 = new SpinBirdEnemy(dynamic_cast<BalloonBossEnemy*>(host));
			s3->SetPosition(host->GetPosition().x, host->GetPosition().y - 300);

			SpinBirdEnemy* s4 = new SpinBirdEnemy(dynamic_cast<BalloonBossEnemy*>(host));
			s4->SetPosition(host->GetPosition().x, host->GetPosition().y + 300);

			this->levelHandler->enemiesRef->push_back(s1);
			this->levelHandler->enemiesRef->push_back(s2);
			this->levelHandler->enemiesRef->push_back(s3);
			this->levelHandler->enemiesRef->push_back(s4);
		}
	}
}

void LevelSpawner::SpawnWizardBurst(WizardBossEnemyP1* host)
{
	Vector2 bossPos = host->GetPosition();

	//front
	WizardBulletEnemy* e1 = new WizardBulletEnemy();
	e1->SetPosition(bossPos.x - 200.0f, bossPos.y);
	e1->SetBaseVelocity(-3.0f, 0.0f);

	//front up
	WizardBulletEnemy* e2 = new WizardBulletEnemy();
	e2->SetPosition(bossPos.x - 200.0f * cosf(PI / 4.0f), bossPos.y + 200.0f * sinf(PI / 4.0f));
	e2->SetBaseVelocity(-3.0f * cosf(PI / 4.0f), 3.0f * sinf(PI / 4.0f));

	//most up
	WizardBulletEnemy* e3 = new WizardBulletEnemy();
	e3->SetPosition(bossPos.x - 200.0f * cosf(PI / 3.0f), bossPos.y + 200.0f * sinf(PI / 3.0f));
	e3->SetBaseVelocity(-3.0f * cosf(PI / 3.0f), 3.0f * sinf(PI / 3.0f));

	//front down
	WizardBulletEnemy* e4 = new WizardBulletEnemy();
	e4->SetPosition(bossPos.x - 200.0f * cosf(PI / 4.0f), bossPos.y - 200.0f * sinf(PI / 4.0f));
	e4->SetBaseVelocity(-3.0f * cosf(PI / 4.0f), -3.0f * sinf(PI / 4.0f));

	//most down
	WizardBulletEnemy* e5 = new WizardBulletEnemy();
	e5->SetPosition(bossPos.x - 200.0f * cosf(PI / 3.0f), bossPos.y - 200.0f * sinf(PI / 3.0f));
	e5->SetBaseVelocity(-3.0f * cosf(PI / 3.0f), -3.0f * sinf(PI / 3.0f));

	//30 degrees up
	WizardBulletEnemy* e6 = new WizardBulletEnemy();
	e6->SetPosition(bossPos.x - 200.0f * cosf(PI / 6.0f), bossPos.y + 200.0f * sinf(PI / 6.0f));
	e6->SetBaseVelocity(-3.0f * cosf(PI / 6.0f), 3.0f * sinf(PI / 6.0f));

	//30 degrees down
	WizardBulletEnemy* e7 = new WizardBulletEnemy();
	e7->SetPosition(bossPos.x - 200.0f * cosf(PI / 6.0f), bossPos.y - 200.0f * sinf(PI / 6.0f));
	e7->SetBaseVelocity(-3.0f * cosf(PI / 6.0f), -3.0f * sinf(PI / 6.0f));

	this->levelHandler->enemiesRef->push_back(e1);
	this->levelHandler->enemiesRef->push_back(e2);
	this->levelHandler->enemiesRef->push_back(e3);
	this->levelHandler->enemiesRef->push_back(e4);
	this->levelHandler->enemiesRef->push_back(e5);
	this->levelHandler->enemiesRef->push_back(e6);
	this->levelHandler->enemiesRef->push_back(e7);
}


//spawn 3 small slimes at pos
void LevelSpawner::SpawnSlimeBurst(Vector2 pos)
{
	SlimeEnemy* e1 = new SlimeEnemy(true);
	e1->SetPosition(pos.x + GetRandomFloat(-50.0f,50.0f), pos.y + GetRandomFloat(-50.0f, 50.0f));

	SlimeEnemy* e2 = new SlimeEnemy(true);
	e2->SetPosition(pos.x + GetRandomFloat(-50.0f, 50.0f), pos.y + GetRandomFloat(-50.0f, 50.0f));

	SlimeEnemy* e3 = new SlimeEnemy(true);
	e3->SetPosition(pos.x + GetRandomFloat(-50.0f, 50.0f), pos.y + GetRandomFloat(-50.0f, 50.0f));

	this->levelHandler->enemiesRef->push_back(e1);
	this->levelHandler->enemiesRef->push_back(e2);
	this->levelHandler->enemiesRef->push_back(e3);
}



bool LevelSpawner::IsFinishedSpawning()
{
	int lastFrame = 0;

	//find the frame of the last enemy spawned in this level
	for (const auto& [enemyID,framesToSpawn] : this->spawnMap)
	{
		lastFrame = std::max((int)framesToSpawn.back(), lastFrame);
	}

	return this->levelHandler->currentLevelFrameCount > lastFrame;
}

int LevelSpawner::GetCurrentLevelLength()
{
	int lastFrame = 0;

	//find the frame of the last enemy spawned in this level
	for (const auto& [enemyID, framesToSpawn] : this->spawnMap)
	{
		lastFrame = std::max((int)framesToSpawn.back(), lastFrame);
	}

	return lastFrame;
}

void LevelSpawner::SpawnEnemyByID(int id)
{
	Enemy* e;

	BatEnemy* b;

	switch (id)
	{
	case 1:
		e = new SoldierEnemy();
		break;

	case 2:
		e = new KoopaEnemy();
		break;

	case 3:
		e = new RedKoopaEnemy();
		break;

	case 4:
		e = new WolfEnemy();
		break;

	case 5:
		b = new BatEnemy();
		b->SetAmplitude(GetRandomFloat(1, 5));
		if (GetRandomValue(1, 2) == 1) b->upStart = true;
		e = b;
		break;

	case 6:
		e = new SlimeEnemy(false);
		break;

	case 7:
		e = new BalloonBossEnemy();
		break;

	case 8:
		e = new BalloonBulletEnemy();
		break;
	
	case 9:
		e = new BeetleEnemy();
		break;

	case 10:
		e = new BlackSoldierEnemy();
		break;

	case 11:
		e = new WizardBossEnemyP1();
		break;

	case 12:
		e = new WizardBulletEnemy();
		break;

	case 13:
		e = new WizardFireEnemy();
		break;

	default:
		std::cout << "Enemy id: " << id << " not found. Spawning soldier.";
		e = new SoldierEnemy();
		break;
	}

	if (e->GetID() == 7)
	{
		e->SetPosition((float)screenWidth, (screenHeight / 2) + (menuBoundaryY / 2));
		this->levelHandler->enemiesRef->push_back(e);
	}

	else if (e->GetID() == 11)
	{
		e->SetPosition((float)halfwayLevelX, (float)halfwayLevelY);
		this->levelHandler->enemiesRef->push_back(e);
	}

	else
	{
		e->SetPosition((float)screenWidth, (float)GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
		this->levelHandler->enemiesRef->push_back(e);
	}	
}

void LevelSpawner::SetSpawnMap(int level)
{
	this->spawnMap.clear();

	switch (level)
	{
	case 1:
		this->spawnMap[1] = { 60,    240, 241,    500, 501,     800, 801, 850,    1100,1101,1102,    1400,1401 }; 
		this->spawnMap[2] = {																						1750 };
		break;

	case 2:
		this->spawnMap[1] = { 60,           400,			700,701,                1500,								2800};
		this->spawnMap[2] = { 60,  300,301,     600,601,            1000,1001,      1500,								2800};
		this->spawnMap[3] = {																		2200,				2800};
		break;

	case 3:
		for (int i = 60; i < 1500; i += 200)
		{
			this->spawnMap[5].push_back(i);
		}

		for (int i = 2500; i <= 2504; i++)
		{
			this->spawnMap[5].push_back(i);
		}

		

		this->spawnMap[1] = { 60, 61, 62,  400,401,402,403,    800,801,802,			1500,1501};
		this->spawnMap[2] = {												1000,					2000,				2500,2502,2503};
		this->spawnMap[3] = {												1000,1001,              2000,2001,2003 };
		
		break;

	case 4:
		this->spawnMap[1] = { 200,500,700,900,1100,1300,1500,1700,1800,2000,																					2800,2801};
		this->spawnMap[4] = { 60,         300,           600,601,        1001,1002,1003,         1800,1800,			2300,2301,2302,2303,2304,2305,2306,          2800,2801,2802,2803};
		this->spawnMap[3] = { 600,601,										1001,1002,				 1800,														2801,2802,2803,2804	};


		break;
		
	case 5:
		this->spawnMap[6] = { 60, 300,300,300,   750,750,750,      1200,1200,1200,1200,            2000,2000,2000,2000,2000,           2600,2600,2600,2600,2600 };
		this->spawnMap[1] = { 60, 300, 1200, 2000, 2600 };
		this->spawnMap[5] = { 1500,1520,1540,1560 };
		break;

	case 6:
		this->spawnMap[7] = { 1 };
		//this->spawnMap[8] = { 4,5,6,7,8 };
		break;

	case 7:
		this->spawnMap[9] = { 60,       500,500,500,				1000,1000,1000,              1500,1500,          2000,2000,2000,         2500,2500,2500,        3000, 3000, 3000, 3000 };
		this->spawnMap[3] = {			500,						1000,																	2500,2500,2500};
		this->spawnMap[4] = {																	1500,1500,1500, };
		this->spawnMap[2] = { 1000,																					2000,2000,2000,2000, };
		break;

	case 8:

		this->spawnMap[4] = {				500,											2000,2101,2202,2300,				};
		this->spawnMap[9] = {				500,		1000,1001,1002,		1500, 1500,								3000		};
		this->spawnMap[10] = { 60,			500,		1000,				1500, 1500 ,							3000, 3000	};
		this->spawnMap[6] = {							1000,1000,1000,     1500,1500,1500,    2000,2000,2000};
		break;

	case 9:
		for (int i = 60; i <= 3000; i += 60)
		{
			this->spawnMap[1].push_back(i);
		}

		for (int i = 60; i <= 3000; i += 50)
		{
			this->spawnMap[5].push_back(i);
		}



		for (int j = 0; j <= 3000; j += 500)
		{
			for (int i = 0; i < 5 + (j / 500) * 2; i += 1)
			{
				this->spawnMap[3].push_back(j);
			}
		}
		break;

	case 10:

		this->spawnMap[10] = { 60,60,60,60,       500,500,500,500,          1000,1000,1000,1000,   1500,1500,1500,1500,   2000,2000,2000,2000,  2500,2500,2500,2500,   3000,3000,3000,3000,3000 };
		this->spawnMap[2] = {                300,300,              700,700,700,					1200,1200,1200,1200,1700,1700,1700,1700,1700,  2200,2200,2200,2200,2200,2200,     2700,2700,2700,2700,2700,2700,2700,2700};


		break;
	case 11:
		for (int i = 0; i <= 500; i += 20)
		{
			this->spawnMap[1].push_back(i);
		}

		for (int i = 500; i <= 1000; i += 20)
		{
			this->spawnMap[2].push_back(i);
		}

		for (int i = 1000; i <= 1500; i += 10)
		{
			this->spawnMap[5].push_back(i);
		}

		for (int i = 1500; i <= 2000; i += 20)
		{
			this->spawnMap[3].push_back(i);
		}

		for (int i = 2000; i <= 2500; i += 20)
		{
			this->spawnMap[4].push_back(i);
		}

		for (int i = 2500; i <= 3000; i += 35)
		{
			this->spawnMap[6].push_back(i);
		}

		for (int i = 3000; i <= 3500; i += 50)
		{
			this->spawnMap[9].push_back(i);
		}

		for (int i = 3500; i <= 4000; i += 60)
		{
			this->spawnMap[10].push_back(i);
		}

		for (int j = 1; j <= 10; j++)
		{
			if (j != 7 && j != 8)
			{
				for (int i = 0; i <= 5; i++)
				{
					this->spawnMap[j].push_back(4500);
				}
			}
		}

		









		break;



	case 12:
		this->spawnMap[11] = { 1 };
		break;

	default:
		std::cout << "Cannot set spawnmap for level " << level << '\n';
		break;

	}
}
