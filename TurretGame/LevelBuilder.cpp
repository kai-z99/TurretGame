#include "LevelBuilder.h"
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

LevelBuilder::LevelBuilder(LevelHandler* levelHandler)
{
	this->levelHandler = levelHandler;

	for (int i = 1; i <= 5; i++)
	{
		this->spawnMap[i] = {};
	}
}

void LevelBuilder::HandleCurrentLevelSpawning()
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

void LevelBuilder::SpawnEnemyByID(int id)
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

void LevelBuilder::SetSpawnMap(int level)
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
		for (int i = 0; i < 1000; i+= 50)
		{
			this->spawnMap[5].push_back(i);
		}
		
		break;

	default:
		std::cout << "Cannot set spawnmap for level " << level << '\n';

	}
	
}
