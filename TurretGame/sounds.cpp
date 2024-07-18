#include "sounds.h"

std::vector<Music> tracks;
std::vector<Sound> soundEffects;

std::vector<const char*> trackFilePaths = {
    "Tracks/World1.mp3",               //0
    "Tracks/World2.mp3",               //1
    "Tracks/World3.mp3",               //2
    "Tracks/LevelSelect.mp3",          //3
    "Tracks/Boss1.mp3",                //4
    "Tracks/Boss2.mp3",                //5
};

std::vector<const char*> soundEffectFilePaths = {
    "Sounds/ShootBasic.ogg",           //0
    "Sounds/ShootElectric.ogg",        //1
    "Sounds/Explosion1.ogg",           //2
    "Sounds/PowerUp.ogg",              //3
    "Sounds/HitBasic.ogg",             //4
};

void LoadAllSounds()
{
    InitAudioDevice();
    //tracks
    for (const char* path : trackFilePaths)
    {
        tracks.push_back(LoadMusicStream(path));
    }

    //sound effects
    for (const char* path : soundEffectFilePaths)
    {
        soundEffects.push_back(LoadSound(path));
    }

}

void UnloadAllSounds()
{
    for (Music& m : tracks)
    {
        UnloadMusicStream(m);
    }

    for (Sound& s : soundEffects)
    {
        UnloadSound(s);
    }

    CloseAudioDevice();
}
