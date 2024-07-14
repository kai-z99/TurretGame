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
		this->PlaySoundEffect(0); // bullet connect effect
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
}


void SoundHandler::PlaySoundEffect(int id)
{
	PlaySound(soundEffects[id]);
}

void SoundHandler::PlayMusic(int id)
{
	StopMusicStream(*this->currentSong);
	this->currentSong = &tracks[id];
	PlayMusicStream(*this->currentSong);
}
