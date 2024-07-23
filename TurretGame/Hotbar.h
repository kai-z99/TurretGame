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
	Hotbar();
	void Draw(CurrentLevelStats& currentLevelStats, GameStats& gamestats, unsigned int currentLevelFrame, int currentLevelLength);
	void Update(unsigned int frame, std::unordered_map<TurretAbility, AbilityInfo>& abilityStates);
	void HandleInput();

	std::vector<TurretAbility> GetActiveAbilityButtons();

private:
	void DrawLevelProgressBar(unsigned int frame, int levelLength);
	std::vector<Button*> buttons;
};