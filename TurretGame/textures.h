#pragma once
#include "raylib.h"
#include <vector>

extern std::vector<Texture2D> textures;

void LoadAllTextures();
void UnloadAllTextures();

