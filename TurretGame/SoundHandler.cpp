#include "SoundHandler.h"
#include <iostream>
#include "Game.h"
#include "Enemy.h"
#include "Bullet.h"

#include "sounds.h"

SoundHandler::SoundHandler(Game* game)
{
	this->game = game;
	this->currentSong = nullptr;
}

void SoundHandler::Update()
{
	if (this->currentSong != nullptr)
	{
		UpdateMusicStream(*this->currentSong);
	}
}

void SoundHandler::HandleBulletCollisionSound(Bullet* b)
{
	switch (b->GetID())
	{
	default:
		this->PlaySoundEffect(4); // bullet connect effect
		break;
	}
}

void SoundHandler::HandleBulletShootSound(Bullet* b)
{
	switch (b->GetID())
	{
	default:
		this->PlaySoundEffect(0); // bullet shoot effect
		break;
	}
}

void SoundHandler::HandleActivateAbilitySound(TurretAbility a)
{
	switch (a)
	{
	default:
		PlaySoundEffect(3);
		break;
	}
}

void SoundHandler::HandleEnterLevel(int level)
{
	if (level > 0 && level < 6) this->PlayMusic(0);    // world 1
	else if (level == 6) this->PlayMusic(4); //ballon boss
	else if (level > 6 && level < 10) this->PlayMusic(1); // world 2
	else if (level == 10) this->PlayMusic(0); // wrld 2 boss
	else this->PlayMusic(0);

}

void SoundHandler::HandleGoToLevelSelect()
{
	this->PlayMusic(3);
}

void SoundHandler::HandleGoToMainMenu()
{
	this->PlayMusic(4);
}


void SoundHandler::PlaySoundEffect(int id)
{
	PlaySound(soundEffects[id]);
}

void SoundHandler::PlayMusic(int id)
{
	if (this->currentSong != nullptr) StopMusicStream(*this->currentSong);
	this->currentSong = &tracks[id];
	PlayMusicStream(*this->currentSong);
}
