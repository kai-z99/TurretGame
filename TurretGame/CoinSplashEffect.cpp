#include "CoinSplashEffect.h"
#include <string>

CoinSplashEffect::CoinSplashEffect(Vector2 pos, int amount)
{
	this->framesLeft = 60;
	this->coinAmount = amount;
	this->position = pos;
}

void CoinSplashEffect::UpdateAndDraw()
{
	if (this->framesLeft > 0)
	{
		std::string text = "+" + std::to_string(this->coinAmount);
		float fontsize = 30.0f;
		float spacing = 3.0f;
		Vector2 textDimensions = MeasureTextEx(GetFontDefault(), text.c_str(), fontsize, 5);
		float xPos = this->position.x - (textDimensions.x / 2);
		float yPos = this->position.y - (textDimensions.y / 2);

		DrawTextEx(GetFontDefault(), text.c_str(), { xPos, yPos }, fontsize, spacing, GREEN);

		this->position.y -= 1;
		this->framesLeft -= 1;
	}
	
}
