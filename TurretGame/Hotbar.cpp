#include "Hotbar.h"
#include <string>
#include "constants.h"
#include "UpgradeButton.h"


Hotbar::Hotbar()
{
	for (int i = 0; i <= 5; i++)
	{
		int buttonY = (menuBoundaryY / 2) - (UpgradeButton::height / 2);

		this->buttons.push_back(new UpgradeButton(300 + i * 150, buttonY, i));
	}
}

void Hotbar::Draw(GameStats* gameStats)
{
	//draw the background
	DrawRectangle(0, 0, screenWidth, menuBoundaryY, GRAY);

	//draw health
	std::string text = "HP: " + std::to_string(gameStats->health);
	float fontsize = 36.0f;
	float spacing = 4.0f;
	Vector2 textDimensions = MeasureTextEx(GetFontDefault(), text.c_str(), fontsize, 5);
	float xPos = ((float)deathBoundaryX / 2) - (textDimensions.x / 2);
	float yPos = ((float)menuBoundaryY / 3) - (textDimensions.y / 2);

	DrawTextEx(GetFontDefault(), text.c_str(), { xPos ,yPos }, fontsize, spacing, RED);

	//draw coins (same fontsize and spacing as health)
	text = "Coins: " + std::to_string(gameStats->coins);
	textDimensions = MeasureTextEx(GetFontDefault(), text.c_str(), fontsize, 5);
	xPos = ((float)deathBoundaryX / 2) - (textDimensions.x / 2);
	yPos = (2*(float)menuBoundaryY / 3) - (textDimensions.y / 2);

	DrawTextEx(GetFontDefault(), text.c_str(), { xPos ,yPos }, fontsize, spacing, RED);

	for (Button* b : this->buttons)
	{
		b->Draw();
	}

}

void Hotbar::Update(unsigned int frame)
{
	for (Button* b : this->buttons)
	{
		b->Update(GetMouseX(), GetMouseY());
	}
}
