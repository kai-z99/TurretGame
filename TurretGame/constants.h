#pragma once
#include "raylib.h"
#include <vector>
#include <unordered_map>

const int screenWidth = 1920;
const int screenHeight = 1080;
const int deathBoundaryX = 240;
const int menuBoundaryY = 150;
const int worldBoundaries[3] = {1200,3000,4500};

//WORLD MAP

//id : positions
const std::unordered_map<int, std::vector<Vector2>> decorationPositions =
{
	{0, { {100,500},{700,300}, {1159,781}, {1590, 245} } },
	{1, { {800,500},{750,200},{500,100}, {260, 830} } },
	{2, { {260,500},{700,1000}, {1500, 800}}},
	{3, { {500,800}, {1362, 255}}},

};

