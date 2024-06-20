#include "AbilityButton.h"
#include <iostream>
#include <string>
#include "textures.h"

const int AbilityButton::width = 100;
const int AbilityButton::height = 100;

AbilityButton::AbilityButton(int posX, int posY, TurretAbility ability)
{
	this->position = { (float)posX, (float)posY };
	this->ability = ability;

	switch (ability)
	{
	case (Rapidfire):
		this->texture = &textures[10];
		break;
		
	case (SpecialRapidfire):
		this->texture = &textures[12];
		break;
	
	case (Explosive):
		this->texture = &textures[13];
		break;

	case (Ice):
		this->texture = &textures[15];
		break;

	default:
		std::cout << "No texture found. Drawing default texture." << '\n';
		this->texture = &textures[2];
		break;
	}
	
}

void AbilityButton::Draw()
{
	//Draw bg square
	Color col;
	if (this->isHeld) col = DARKBLUE;
	else if (this->isHovering) col = { 0, 0, 255, 50 };
	else col = WHITE;

	DrawRectangle((int)this->position.x, (int)this->position.y, this->width, this->height, col );

	//draw icon
	DrawTexture(*this->texture, (int)this->position.x + 10, (int)this->position.y + 10, WHITE);

	//draw progress bar
	int w = 70;
	int h = 10;

	//this->barProgress = (float)this->currentCharges / this->totalCharges;

	DrawRectangle((int)(this->position.x + (AbilityButton::width / 2.0f)) - (int)(w / 2.0f), (int)this->position.y + 108, w, h, RED);
	DrawRectangle((int)(this->position.x + (AbilityButton::width / 2.0f)) - (int)(w / 2.0f), (int)this->position.y + 108, (int)(w * barProgress), h, GREEN);


	//draw cooldown opaque bar
	DrawRectangle((int)this->position.x, (int)this->position.y, this->width, (int)(this->height * this->cooldownProgress), {0,0,0,170});
	
	//draw id, temp?
	DrawText(std::to_string(this->ability + 1).c_str(), (int)this->position.x - 15, (int)this->position.y, 20, DARKBLUE);

	
}

void AbilityButton::Update(int mouseX, int mouseY)
{
	Button::Update(mouseX, mouseY);
}

bool AbilityButton::MouseCollide(int mouseX, int mouseY)
{
	Rectangle rec = { this->position.x, this->position.y, this->width, this->height };
	return CheckCollisionPointRec({ (float)mouseX, (float)mouseY }, {rec});
}

void AbilityButton::SetBarProgress(float barProgress)
{
	this->barProgress = barProgress;
}

void AbilityButton::SetCooldownProgress(float barProgress)
{
	this->cooldownProgress = barProgress;
}

TurretAbility AbilityButton::GetAbility()
{
	return this->ability;
}

