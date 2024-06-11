#include "VisualEffect.h"
#include <string>


void VisualEffect::UpdateAndDraw() //debug draw
{
	DrawCircleLines(this->position.x, this->position.y, 20.0f, BLUE);
	DrawText("EFFECT HERE", this->position.x, this->position.y, 30.0f, RED);
}

bool VisualEffect::isActive()
{
	return this->framesLeft > 0;
}

