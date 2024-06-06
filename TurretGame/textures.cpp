#include "textures.h"

std::vector<Texture2D> textures;

std::vector<const char*> textureFilePaths = {
    "Sprites/scarfy.png",               //0
    "Sprites/turret.png",               //1
    "Sprites/TurretBullet.png",         //2
    "Sprites/koopa.png",                //3
    "Sprites/redKoopa.png",             //4
    "Sprites/redKoopaShell.png",        //5
    "Sprites/galaxy.png",               //6
    "Sprites/ShockwaveBullet.png",      //7
    "Sprites/bat.png",                  //8
    "Sprites/explosion.png"             //9
};

void LoadAllTextures() 
{
    for (const char* path : textureFilePaths)
    {
        textures.push_back(LoadTexture(path));
    }

}

void UnloadAllTextures() 
{
    for (Texture2D t : textures)
    {
        UnloadTexture(t);
    }
}