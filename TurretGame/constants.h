#pragma once
#include "raylib.h"
#include <vector>
#include <unordered_map>

const int screenWidth = 1920;
const int screenHeight = 1080;
const int deathBoundaryX = 240;
const int menuBoundaryY = 150;
const int halfwayLevelY = 615;
const int worldBoundaries[3] = {1200,3000,4500};

//WORLD MAP
namespace MapPositions
{
    //id : positions
    const std::unordered_map<int, std::vector<Vector2>> decorationPositions =
    {
        {0, { {100,500},{700,300}, {1159,781}, {1590, 245} } },
        {1, { {800,500},{750,200},{500,100}, {260, 830} } },
        {2, { {260,500},{700,1000}, {1500, 800}}},
        {3, { {500,800}, {1362, 255}}},

        {4, { {2400,800}, {2162, 255}, {1900 + 1164, 551}, {1900 + 1444, 929}}},
        {5, { {1900 + 1442, 325}, {1800 + 284, 482}, {1890, 852} }},
        {6, { {1900 + 635, 670}, {1900,100}, {1900 + 948, 106} }},
        {7, { {2400, 110}, }},
        {8, {  {1900 + 1086, 268}}},
        {9, { {1900 + 947, 923}, {1950,1000}, {1900 + 1295, 132}}},


    };



    const std::unordered_map<int, Vector2> levelPositions =
    {
        {1, {200, 500}},
        {2, {500, 500}},
        {3, {700, 700}},
        {4, {1000, 550}},
        {5, {1200, 400}},
        {6, {1400, 600}},
        {7, {1900, 700}},
        {8, {2200, 650}},
        {9, {2360, 450}},
        {10, {2700, 500}},
        {11, {2970, 750}},
        {12, {3250, 600}},
    };
}
