#include "textures.h"

Texture2D scarfyTexture;
Texture2D koopaTexture;
Texture2D turretTexture;
Texture2D turretBulletTexture;
Texture2D galaxyBGTexture;

void LoadAllTextures() 
{
    scarfyTexture = LoadTexture("Sprites/scarfy.png");
    turretTexture = LoadTexture("Sprites/turret.png");
    turretBulletTexture = LoadTexture("Sprites/TurretBullet.png");
    koopaTexture = LoadTexture("Sprites/koopa.png");
    galaxyBGTexture = LoadTexture("Sprites/galaxy.png");
}

void UnloadAllTextures() 
{
    UnloadTexture(scarfyTexture);
    UnloadTexture(turretTexture);
    UnloadTexture(turretBulletTexture);
    UnloadTexture(galaxyBGTexture);
}