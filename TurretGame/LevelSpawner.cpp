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

LevelSpawner::LevelSpawner(LevelHandler* levelHandler)
{
	this->levelHandler = levelHandler;
}

void LevelSpawner::HandleCurrentLevelSpawning()
{
	//for every enemy id
	for (const auto& pair : this->spawnMap)
	{
		//for each frame they should spawn
		for (const int& frame : pair.second)
		{
			//if thats the current frame
			if (levelHandler->currentLevelFrameCount == frame)
			{
				this->SpawnEnemyByID(pair.first);
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
	for (const auto& pair : this->spawnMap)
	{
		lastFrame = std::max((int)pair.second.back(), lastFrame);
	}

	return this->levelHandler->currentLevelFrameCount > lastFrame;
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
		b->SetAmplitude(GetRandomFloat(1, 10));
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
	default:
		std::cout << "Enemy id: " << id << " not found. Spawning soldier.";
		e = new SoldierEnemy();
		break;
	}

	if (e->GetID() != 7)
	{
		e->SetPosition((float)screenWidth, (float)GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
		this->levelHandler->enemiesRef->push_back(e);
	}

	else
	{
		e->SetPosition((float)screenWidth, (screenHeight / 2) + (menuBoundaryY / 2));
		this->levelHandler->enemiesRef->push_back(e);

	}
	
}

void LevelSpawner::SetSpawnMap(int level)
{
	this->spawnMap.clear();

	switch (level)
	{
	case 1:
		this->spawnMap[1] = { 100,200,300,400,500 }; //temp
		this->spawnMap[6] = { 1,200,300,400,500 }; //temp
		break;

	case 2:
		this->spawnMap[2] = { 50,100,422 };
		break;

	case 3:
		for (int i = 0; i < 8000; i+= 1)
		{
			this->spawnMap[5].push_back(i);
		}

		for (int i = 0; i < 8000; i += 1)
		{
			this->spawnMap[4].push_back(i);
		}

		for (int i = 0; i < 8000; i += 1)
		{
			this->spawnMap[3].push_back(i);
		}

		for (int i = 0; i < 8000; i += 1)
		{
			this->spawnMap[2].push_back(i);
		}

		break;

	case 4:
		this->spawnMap[3] = { 300,600 };
		this->spawnMap[4] = { 200,500,550 };
		break;
		
	case 5:
		this->spawnMap[1] = { 50,150,400 };
		this->spawnMap[4] = { 100,200 };
		this->spawnMap[3] = { 0, 10, 333 };
		break;

	case 6:
		this->spawnMap[7] = { 1 };
		//this->spawnMap[8] = { 4,5,6,7,8 };
		break;

	case 7:
		this->spawnMap[9] = { 1,102,153,664 };

		this->spawnMap[3] = { 501,602,703,804,905,906 };

	default:
		std::cout << "Cannot set spawnmap for level " << level << '\n';
		break;

	}
}
