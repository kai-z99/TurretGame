#include "BombExplosion.h"
#include "TextureLoop.h"
#include "textures.h"
#include "Enemy.h"

float BombExplosion::damage = 300.0f;
int BombExplosion::knockbackFrames = 30;
float BombExplosion::radius = 300.0f;
float BombExplosion::bulletRadius = 150.0f;

BombExplosion::BombExplosion(int posX, int posY, bool bullet)
{
	this->id = 1;
	this->position = { (float)posX, (float)posY };
	this->isActive = true;
	this->isDetonateFrame = true;
	this->framesLeft = 90;
	this->isBullet = bullet;

	if (!this->isBullet)
	{
		this->textureLoop = new TextureLoop(&textures[9], 9, 8.0f * (BombExplosion::radius / 300.0f), this->position); //scale it based on explosion size
		this->animSpeed = 10;
	}
	else //radius is fixed at 100;
	{
		this->textureLoop = new TextureLoop(&textures[9], 9, 3.0f, this->position);
		this->animSpeed = 5;
	}
	
}

void BombExplosion::Update(unsigned int frame)
{
	if (this->framesLeft != 90) this->isDetonateFrame = false; //mkae it middle?

	//update textureLoop

	if (this->framesLeft > 0)
	{
		if (this->framesLeft % this->animSpeed == 0) this->textureLoop->NextFrame();
	}

	else this->isActive = false;

	this->textureLoop->Update();


	this->framesLeft--;
	if (this->isBullet) this->framesLeft--; // twice as fast anim in bullet

}

void BombExplosion::Draw()
{
	//DrawCircleLines(this->position.x, this->position.y, BombExplosion::bulletRadius, RED); // temp
	this->textureLoop->Draw();
}

bool BombExplosion::EnemyCollided(Enemy* e)
{
	if (!isBullet) return CheckCollisionCircleRec(this->position, BombExplosion::radius, e->GetHitbox());
	else return CheckCollisionCircleRec(this->position, BombExplosion::bulletRadius, e->GetHitbox());
}
