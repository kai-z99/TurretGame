#include "BombExplosion.h"
#include "TextureLoop.h"
#include "textures.h"
#include "Enemy.h"

BombExplosion::BombExplosion(int posX, int posY)
{
	this->id = 1;
	this->position = { (float)posX, (float)posY };
	this->hitboxRadius = 250.0f;
	this->isActive = true;
	this->isDetonateFrame = true;
	this->framesLeft = 90;
	this->textureLoop = new TextureLoop(&textures[9], 9, 6.0f, this->position);

	this->damage = 10;
	this->knockbackFrames = 30;
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
	//DrawCircleLines(this->position.x, this->position.y, this->hitboxRadius, RED); // temp
	this->textureLoop->Draw();
}

bool BombExplosion::EnemyCollided(Enemy* e)
{
	return CheckCollisionCircleRec(this->position, this->hitboxRadius, e->GetHitbox());
}

int BombExplosion::GetDamage() const
{
	return this->damage;
}

int BombExplosion::GetKnockbackFrames() const
{
	return this->knockbackFrames;
}
