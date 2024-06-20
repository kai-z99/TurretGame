#include "AreaEffect.h"

void AreaEffect::Update(unsigned int frame)
{
}

void AreaEffect::Draw()
{
	DrawCircleLines((int)this->position.x, (int)this->position.y, 30.0f, RED);
	DrawText("AOE HERE", (int)this->position.x, (int)this->position.y, 20, RED);
}

int AreaEffect::GetID()
{
	return this->id;
}

Vector2 AreaEffect::GetPosition() const
{
	return this->position;
}
