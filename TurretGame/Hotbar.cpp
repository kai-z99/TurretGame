#include "Hotbar.h"
#include <string>
#include "constants.h"
#include "AbilityButton.h"
#include "types.h"

#include "raymath.h"



Hotbar::Hotbar()
{
	//create the buttons
	int buttonY = (menuBoundaryY / 2) - (AbilityButton::height / 2);

	for (int i = 0; i <= 4; i++)
	{
		this->buttons.push_back(new AbilityButton(300 + i * 150, buttonY, static_cast<TurretAbility>(i)));
	}
}

void Hotbar::Draw(CurrentLevelStats& currentLevelStats, GameStats& gamestats, unsigned int currentLevelFrame, int currentLevelLength)
{
	//draw the background
	DrawRectangle(0, 0, screenWidth, menuBoundaryY, GRAY);

	//draw health
	std::string text = "HP: " + std::to_string(currentLevelStats.health);
	float fontsize = 36.0f;
	float spacing = 4.0f;
	Vector2 textDimensions = MeasureTextEx(GetFontDefault(), text.c_str(), fontsize, spacing);
	float xPos = ((float)deathBoundaryX / 2) - (textDimensions.x / 2);
	float yPos = ((float)menuBoundaryY / 3) - (textDimensions.y / 2);

	DrawTextEx(GetFontDefault(), text.c_str(), { xPos ,yPos }, fontsize, spacing, RED);

	//draw coins (same fontsize and spacing as health)
	text = "Coins: " + std::to_string(gamestats.totalCoins) + " C";
	fontsize = 30.0f;

	textDimensions = MeasureTextEx(GetFontDefault(), text.c_str(), fontsize, spacing);
	xPos = ((float)deathBoundaryX / 2) - (textDimensions.x / 2);
	yPos = (2*(float)menuBoundaryY / 3) - (textDimensions.y / 2);

	DrawTextEx(GetFontDefault(), text.c_str(), { xPos ,yPos }, fontsize, spacing, RED);

	//draw buttons
	for (Button* b : this->buttons)
	{
		b->Draw();
	}

	//draw level progress
	this->DrawLevelProgressBar(currentLevelFrame, currentLevelLength);

}

void Hotbar::Update(unsigned int frame, std::unordered_map<TurretAbility, AbilityInfo>& abilityStates)
{
	// for every ability button set its charge bar and cooldown progress accorrding to thye gamestate
	for (int i = 0; i <= 4; i++)
	{
		//cast button to abilityButton
		AbilityButton* b = dynamic_cast<AbilityButton*>(this->buttons[i]);

		//set cooldown bar based on the ability's cooldown and last use
		//onote: progress == how much the bar is shaded
		float progress = 1.0f - ((float)(frame - abilityStates[b->GetAbility()].lastUsedFrame) / (float)abilityStates[b->GetAbility()].cooldown);
		
		if (progress > 1.0f) progress = 1.0f;
		else if (progress < 0.0f) progress = 0.0f;

		//always shade it fully when no charges are left
		if (abilityStates[b->GetAbility()].charges <= 0)
		{
			progress = 1.0f;
		}

		b->SetCooldownProgress(progress);

		//set charge bar
		b->SetBarProgress((float)abilityStates[b->GetAbility()].charges / (float)abilityStates[b->GetAbility()].maxCharges);

		//replace that spot in the buttons vector with the updated button
		this->buttons[i] = b;

		//THIS COULD BE ONE LINE BUT ITS NOT READABLE.
	}
}

void Hotbar::HandleInput()
{
	//check if mouse selected any button
	for (Button* b : this->buttons)
	{
		b->Update(GetMouseX(), GetMouseY());
	}

	// manually check if keyboard activated ablility buttons.
	for (int i = 0; i <= 4; i++)
	{
		if (IsKeyDown(49 + i))
		{
			this->buttons[i]->isHeld = true;
		}

		else if (IsKeyReleased(49 + i))
		{
			this->buttons[i]->isClicked = true;
		}
	}
}

std::vector<TurretAbility> Hotbar::GetActiveAbilityButtons()
{
	std::vector<TurretAbility> v = {};

	//go through each ability button and check if its clicked. if it is, add to return vector
	for (int i = 0; i <= 4; i++)
	{
		TurretAbility ability = static_cast<TurretAbility>(i);
		if (this->buttons[i]->isClicked)
		{
			v.push_back(dynamic_cast<AbilityButton*>(this->buttons[i])->GetAbility());
		}
	}

	return v;
}

void Hotbar::DrawLevelProgressBar(unsigned int frame, int levelLength)
{
	int barWidth = 500;
	int barHeight = 50;

	float w = (float)barWidth;
	int h = barHeight;
	int posX = 1150;
	int posY = (menuBoundaryY / 2) - (h / 2);

	//progress text
	const char* text = "LEVEL PROGRESS";
	Vector2 textSize = MeasureTextEx(GetFontDefault(),text, 19, 5);
	DrawTextEx(GetFontDefault(), text, { posX + (w / 2) - (textSize.x / 2), (float)posY + h + 16 }, 19, 5, BLACK);

	//boss levels are one frame long
	// 
	//normal level
	if (levelLength > 1)
	{
		//black outline
		DrawRectangle(posX - 5, posY - 5, (int)w + 10, h + 10, BLACK);

		//main bar-------------------------------------
		DrawRectangle(posX, posY, (int)w, h, RED);

		w = (float)barWidth * ((float)frame / (float)levelLength);
		if (w > barWidth) w = (float)barWidth;
		h = barHeight;
		posX = 1150;
		posY = (menuBoundaryY / 2) - (h / 2);

		DrawRectangle(posX, posY, (int)w, h, GREEN);
		//-----------------------------------------------
	}

	//boss level
	else
	{
		//black outline
		DrawRectangle(posX - 5, posY - 5, (int)w + 10, h + 10, BLACK);
		//main bar
		//---------------------------------------------
		DrawRectangle(posX, posY, (int)w, h, BLUE);

		const char* text = "BOSS";
		int textWidth = MeasureText(text, 40);

		//boss text
		DrawText(text, 1150 + (int)(w / 2) - (int)(textWidth / 2.0f), (menuBoundaryY / 2) - (h / 2) + 10, 40, BLACK);
		//---------------------------------------------

	}
	

	
}
