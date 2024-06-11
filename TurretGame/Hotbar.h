#pragma once
#include "raylib.h"
#include <vector>
#include "helpers.h"
#include "types.h"
#include <unordered_map>

class Button;

class Hotbar
{
public:
	Hotbar(std::unordered_map<TurretAbility, AbilityInfo>& abilityDB);
	void Draw(GameStats* gameStats);
	void Update(unsigned int frame, std::unordered_map<TurretAbility, AbilityInfo>& charges);
	void HandleInput();

	std::vector<TurretAbility> GetActiveAbilityButtons(unsigned int frame, std::unordered_map<TurretAbility, AbilityInfo>& abilityStates);

private:
	std::vector<Button*> buttons;
};