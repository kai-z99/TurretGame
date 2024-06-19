#include "Hotbar.h"
#include <string>
#include "constants.h"
#include "AbilityButton.h"


Hotbar::Hotbar(std::unordered_map<TurretAbility, AbilityInfo>& initialAbilityValues)
{
	//create the buttons

	int buttonY = (menuBoundaryY / 2) - (AbilityButton::height / 2);

	for (int i = 0; i <= 5; i++)
	{
		this->buttons.push_back(new AbilityButton(300 + i * 150, buttonY, static_cast<TurretAbility>(i)));
	}
}

void Hotbar::Draw(CurrentLevelStats& currentLevelStats)
{
	//draw the background
	DrawRectangle(0, 0, screenWidth, menuBoundaryY, GRAY);

	//draw health
	std::string text = "HP: " + std::to_string(currentLevelStats.health);
	float fontsize = 36.0f;
	float spacing = 4.0f;
	Vector2 textDimensions = MeasureTextEx(GetFontDefault(), text.c_str(), fontsize, 5);
	float xPos = ((float)deathBoundaryX / 2) - (textDimensions.x / 2);
	float yPos = ((float)menuBoundaryY / 3) - (textDimensions.y / 2);

	DrawTextEx(GetFontDefault(), text.c_str(), { xPos ,yPos }, fontsize, spacing, RED);

	//draw coins (same fontsize and spacing as health)
	text = "Coins: " + std::to_string(currentLevelStats.coinsCollected);
	textDimensions = MeasureTextEx(GetFontDefault(), text.c_str(), fontsize, 5);
	xPos = ((float)deathBoundaryX / 2) - (textDimensions.x / 2);
	yPos = (2*(float)menuBoundaryY / 3) - (textDimensions.y / 2);

	DrawTextEx(GetFontDefault(), text.c_str(), { xPos ,yPos }, fontsize, spacing, RED);

	//draw buttons
	for (Button* b : this->buttons)
	{
		b->Draw();
	}

}

void Hotbar::Update(unsigned int frame, std::unordered_map<TurretAbility, AbilityInfo>& abilityStates)
{
	// for every ability button set its charge bar and cooldown progress accorrding to thye gamestate
	for (int i = 0; i <= 5; i++)
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
	for (int i = 0; i <= 5; i++)
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
	for (int i = 0; i <= 5; i++)
	{
		TurretAbility ability = static_cast<TurretAbility>(i);
		if (this->buttons[i]->isClicked)
		{
			v.push_back(dynamic_cast<AbilityButton*>(this->buttons[i])->GetAbility());
		}
	}

	return v;
}
