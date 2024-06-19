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
	Hotbar(std::unordered_map<TurretAbility, AbilityInfo>& initialAbilityValues);
	void Draw(CurrentLevelStats& currentLevelStats);
	void Update(unsigned int frame, std::unordered_map<TurretAbility, AbilityInfo>& abilityStates);
	void HandleInput();

	std::vector<TurretAbility> GetActiveAbilityButtons();

private:
	std::vector<Button*> buttons;
};