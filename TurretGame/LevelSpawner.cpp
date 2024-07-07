#include "LevelSpawner.h"
#include <iostream>
#include "constants.h"
#include "helpers.h"

#include "Game.h"
#include "LevelHandler.h"

#include "SoldierEnemy.h"
#include "KoopaEnemy.h"
#include "RedKoopaEnemy.h"
#include "WolfEnemy.h"
#include "BatEnemy.h"
#include "SlimeEnemy.h"
#include "BalloonBossEnemy.h"

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

	default:
		std::cout << "Enemy id: " << id << " not found. Spawning soldier.";
		e = new SoldierEnemy();
		break;
	}
	if (e->GetID() != 7)
	{
		e->SetPosition((float)screenWidth, (float)GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
	}

	else
	{
		e->SetPosition((float)screenWidth, (screenHeight / 2) + (menuBoundaryY / 2));
		//e->SetPosition((float)screenWidth / 2, (screenHeight / 2) + (menuBoundaryY / 2));
	}
	
	this->levelHandler->enemiesRef->push_back(e);
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
		break;

	default:
		std::cout << "Cannot set spawnmap for level " << level << '\n';
		break;

	}
}
