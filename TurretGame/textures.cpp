#include "textures.h"

Texture2D scarfyTexture;
Texture2D koopaTexture;
Texture2D redKoopaTexture;
Texture2D redKoopaShellTexture;
Texture2D batTexture;
Texture2D turretTexture;
Texture2D turretBulletTexture;
Texture2D shockwaveBulletTexture;

Texture2D explosionTexture;

Texture2D galaxyBGTexture;

void LoadAllTextures() 
{
    scarfyTexture = LoadTexture("Sprites/scarfy.png");
    turretTexture = LoadTexture("Sprites/turret.png");
    turretBulletTexture = LoadTexture("Sprites/TurretBullet.png");
    koopaTexture = LoadTexture("Sprites/koopa.png");
    redKoopaTexture = LoadTexture("Sprites/redKoopa.png");
    redKoopaShellTexture = LoadTexture("Sprites/redKoopaShell.png");
    galaxyBGTexture = LoadTexture("Sprites/galaxy.png");
    shockwaveBulletTexture = LoadTexture("Sprites/ShockwaveBullet.png");
    batTexture = LoadTexture("Sprites/bat.png");
    explosionTexture = LoadTexture("Sprites/explosion.png");

}

void UnloadAllTextures() 
{
    UnloadTexture(scarfyTexture);
    UnloadTexture(turretTexture);
    UnloadTexture(turretBulletTexture);
    UnloadTexture(galaxyBGTexture);
    UnloadTexture(shockwaveBulletTexture);
    UnloadTexture(batTexture);
    UnloadTexture(explosionTexture);
    UnloadTexture(redKoopaTexture);
    UnloadTexture(redKoopaShellTexture);
}