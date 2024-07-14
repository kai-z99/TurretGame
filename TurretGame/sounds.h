#pragma once

#include "raylib.h"
#include <vector>

extern std::vector<Music> tracks;
extern std::vector<Sound> soundEffects;

void LoadAllSounds();
void UnloadAllSounds();