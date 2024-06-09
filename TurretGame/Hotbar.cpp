#include "Hotbar.h"
#include <string>
#include "constants.h"
#include "AbilityButton.h"


Hotbar::Hotbar()
{
	int buttonY = (menuBoundaryY / 2) - (AbilityButton::height / 2);
	for (int i = 0; i <= 5; i++)
	{
		this->buttons.push_back(new AbilityButton(300 + i * 150, buttonY, static_cast<TurretAbility>(i)));

		//temp, set all abilities to 5 charges
		dynamic_cast<AbilityButton*>(this->buttons[i])->SetTotalCharges(5);
		dynamic_cast<AbilityButton*>(this->buttons[i])->SetCurrentCharges(5);

		//if its an ability button, set its duration to full
		//dynamic_cast<ProgressButton*>(this->buttons[i])->SetProgress(1.0f);
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
	text = "Coins: " + std::to_string(gameStats->coinsCollectedInLevel);
	textDimensions = MeasureTextEx(GetFontDefault(), text.c_str(), fontsize, 5);
	xPos = ((float)deathBoundaryX / 2) - (textDimensions.x / 2);
	yPos = (2*(float)menuBoundaryY / 3) - (textDimensions.y / 2);

	DrawTextEx(GetFontDefault(), text.c_str(), { xPos ,yPos }, fontsize, spacing, RED);

	for (Button* b : this->buttons)
	{
		b->Draw();
	}

}

void Hotbar::Update(unsigned int frame, std::unordered_map<TurretAbility, std::pair<int, int>> charges)
{
	//int i = 0;
	//for (const auto& pair : charges)
	//{
	//	dynamic_cast<AbilityButton*>(this->buttons[i])->SetCurrentCharges(pair.second.first);
	//	i++;
	//}

	// for every ability button, set its charges based on the games charges.
	for (int i = 0; i <= 5; i++)
	{
		//cast button to abilityButton to access GetAbility()
		AbilityButton* b = dynamic_cast<AbilityButton*>(this->buttons[i]);

		//set its charges to the games amount
		b->SetCurrentCharges(charges[b->GetAbility()].first);

		//replace that spot in the buttons vector with the updated amount
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
		if (this->buttons[i]->isClicked)
		{
			v.push_back(dynamic_cast<AbilityButton*>(this->buttons[i])->GetAbility());
		}
	}

	return v;
}
