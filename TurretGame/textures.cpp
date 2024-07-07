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
    "Sprites/explosion.png",            //9
    "Sprites/rapidfire.png",            //10
    "Sprites/fire.png",                 //11
    "Sprites/specialrapidfire.png",     //12
    "Sprites/bomb.png",                 //13
    "Sprites/iceSparkle.png",           //14
    "Sprites/iceIcon.png",              //15
    "Sprites/wolfWalk.png",             //16
    "Sprites/wolfRun.png",              //17
    "Sprites/firebullet.png",           //18
    "Sprites/sniperBullet.png",         //19
    "Sprites/Grass1.png",               //20
    "Sprites/Grass2.png",               //21
    "Sprites/Bush.png",                 //22
    "Sprites/Tree.png",                 //23
    "Sprites/lightningBullet.png",      //24
    "Sprites/slime.png",                //25
    "Sprites/sparkleEffect.png",        //26
    "Sprites/lightningBulletIcon.png",  //27
    "Sprites/bullettest.png",           //28
    "Sprites/grass.png",                //29
    "Sprites/sentryIcon.png",           //30
    "Sprites/balloonWalk.png",          //31

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
    for (const Texture2D& t : textures)
    {
        UnloadTexture(t);
    }

    textures.clear();
}