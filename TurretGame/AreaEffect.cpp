#include "AreaEffect.h"

void AreaEffect::Update(unsigned int frame)
{
}

void AreaEffect::Draw()
{
	DrawCircleLines(this->position.x, this->position.y, 30.0f, RED);
	DrawText("AOE HERE", this->position.x, this->position.y, 20.0f, RED);
}

int AreaEffect::GetID()
{
	return this->id;
}

Vector2 AreaEffect::GetPosition() const
{
	return this->position;
}
