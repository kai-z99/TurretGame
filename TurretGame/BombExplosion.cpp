#include "BombExplosion.h"
#include "TextureLoop.h"
#include "textures.h"
#include "Enemy.h"

float BombExplosion::damage = 300.0f;
int BombExplosion::knockbackFrames = 30;
float BombExplosion::radius = 300.0f;

BombExplosion::BombExplosion(int posX, int posY)
{
	this->id = 1;
	this->position = { (float)posX, (float)posY };
	this->isActive = true;
	this->isDetonateFrame = true;
	this->framesLeft = 90;
	this->textureLoop = new TextureLoop(&textures[9], 9, 8.0f * (BombExplosion::radius / 300.0f), this->position); //scale it based on explosion size
}

void BombExplosion::Update(unsigned int frame)
{
	if (this->framesLeft != 90) this->isDetonateFrame = false; //mkae it middle?

	//update textureLoop

	if (this->framesLeft > 0)
	{
		if (this->framesLeft % 10 == 0) this->textureLoop->NextFrame();
	}

	else this->isActive = false;

	this->textureLoop->Update();

	this->framesLeft--;

}

void BombExplosion::Draw()
{
	//DrawCircleLines(this->position.x, this->position.y, BombExplosion::radius, RED); // temp
	this->textureLoop->Draw();
}

bool BombExplosion::EnemyCollided(Enemy* e)
{
	return CheckCollisionCircleRec(this->position, BombExplosion::radius, e->GetHitbox());
}
