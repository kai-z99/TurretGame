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

	default:
		std::cout << "Enemy id: " << id << " not found. Spawning soldier.";
		e = new SoldierEnemy();
		break;
	}

	e->SetPosition((float)screenWidth, (float)GetRandomValue(menuBoundaryY + 50, screenHeight - 50));
	this->levelHandler->enemiesRef->push_back(e);
}

void LevelSpawner::SetSpawnMap(int level)
{
	this->spawnMap.clear();

	switch (level)
	{
	case 1:
		this->spawnMap[1] = { 100,200,300,400,500 }; //temp
		break;

	case 2:
		this->spawnMap[2] = { 50,100,422 };
		break;

	case 3:
		for (int i = 0; i < 8000; i+= 10)
		{
			this->spawnMap[5].push_back(i);
		}
		break;

	case 4:
		this->spawnMap[3] = { 300,600 };
		this->spawnMap[4] = { 200,500,550 };
	default:
		std::cout << "Cannot set spawnmap for level " << level << '\n';
		break;

	}
}
