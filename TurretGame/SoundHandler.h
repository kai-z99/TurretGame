#pragma once

#include "raylib.h"
#include "types.h"

class Game;
class Bullet;

class SoundHandler
{
public:
	SoundHandler(Game* game);

	void Update();

	// in level
	void HandleBulletCollisionSound(Bullet* b);
	void HandleBulletShootSound(Bullet* b);
	void HandleActivateAbilitySound(TurretAbility a);


private:
	Game* game;
	Music* currentSong;

	void PlaySoundEffect(int id);
	void PlayMusic(int id);
};