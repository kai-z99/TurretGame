#include "VisualEffect.h"
#include <string>


void VisualEffect::UpdateAndDraw() //debug draw
{
	DrawCircleLines((int)this->position.x, (int)this->position.y, 20.0f, BLUE);
	DrawText("EFFECT HERE", (int)this->position.x, (int)this->position.y, 30, RED);
}

bool VisualEffect::isActive()
{
	return this->framesLeft > 0;
}

