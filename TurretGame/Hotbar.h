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
	void Draw(GameStats* gameStats);
	void Update(unsigned int frame, std::unordered_map<TurretAbility, std::pair<int, int>> charges);
	void HandleInput();

	std::vector<TurretAbility> GetActiveAbilityButtons();


private:
	std::vector<Button*> buttons;
};