#include "Turret.h"
#include <iostream>
#include "raymath.h"

#include "types.h"
#include "helpers.h"

#include "TurretBullet.h"
#include "ShockwaveBullet.h"
#include "FireBullet.h"
#include "SniperBullet.h"
#include "LightningBullet.h"
#include "BombBullet.h"
#include "TurretLaser.h"

#include "textures.h" 

float Turret::rapidFirerateMultiplier = 2.0f;
int Turret::rapidFireDuration = 240;

Turret::Turret()
{
    this->angle = 0;

    this->laser = new TurretLaser(this);
    this->laserFrames = 0;

    //Texture init
    this->texture = &textures[1];
    this->textureWidth = this->texture->width;
    this->textureHeight = this->texture->height;
    this->textureSourceRec = { 0.0f, 0.0f, (float)this->textureWidth, (float)this->textureHeight };
    this->textureDestRec = { this->position.x, this->position.y, (float)this->textureWidth, (float)this->textureHeight };
    this->textureOriginPoint = { this->textureWidth / 2.0f, this->textureHeight / 2.0f + 10.0f };

    //gun settings
    this->bulletSpeedMultiplier = 1.0f;

    this->baseFirerate = 1.0f; // in shots per second for turretBullet
    this->currentFirerate = this->baseFirerate;
    
    this->rapidFirerate = this->baseFirerate * Turret::rapidFirerateMultiplier;
    this->rapidFireFrames = 0;

    //initate bullet cooldown map
    std::unordered_map<int, BulletCooldownInfo*>& bcm = this->bulletCooldownMap;

    for (int i = 1; i <= 6; i++)
    {
        bcm[i] = new BulletCooldownInfo();

        if (i == 1) bcm[i]->unlocked = true;
        else bcm[i]->unlocked = false;

        bcm[i]->canShoot = false;
        bcm[i]->lastShotFrame = 0;
        bcm[i]->shotThisFrame = false;
        bcm[i]->firerate = 1.0f;
    }
}

Turret::~Turret()
{
    delete this->laser;
}

void Turret::Draw()
{
    DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, this->angle * RAD2DEG + 90.0f, WHITE);

    //draw laser
    if (this->laser->isActive) this->laser->Draw();
}

void Turret::Update(unsigned int frame, int mouseX, int mouseY)
{
    //update its angle
    this->UpdateAngle(mouseX, mouseY);

    //update this becasue position can change
    this->textureDestRec = { this->position.x, this->position.y, (float)this->textureWidth, (float)this->textureHeight };

    //update the laser
    if (this->laserFrames > 0)
    {
        this->laser->isActive = true;
        this->laser->Update(frame);
        this->laserFrames--;
    }
    else this->laser->isActive = false;


    this->rapidFirerate = this->baseFirerate * Turret::rapidFirerateMultiplier;

    if (this->rapidFireFrames > 0)
    {
        this->currentFirerate = this->rapidFirerate;
        this->rapidFireFrames -= 1;
    }
    else this->currentFirerate = this->baseFirerate;


    //update bullet cooldowns

    //go through each bullet type
    for (auto& [bulletID,cooldownInfo] : this->bulletCooldownMap)
    {
        //if the bullet isnt unlocked, it cannot shoot no matter what.
        if (!cooldownInfo->unlocked)
        {
            cooldownInfo->canShoot = false;
            continue;
        }

        //if this was the frame it shot, update its last shot frame.
        if (cooldownInfo->shotThisFrame)
        {
            cooldownInfo->lastShotFrame = frame;
            cooldownInfo->shotThisFrame = false;
        }

        //check if bullet can be put off cooldown based on its last shot frame

        int baseCooldownFrames;

        // basecooldown of how long each bullet has between shots. firther modified by individual bullet firerate and turretfirerate.
        switch (bulletID)
        {
        //TurretBullet
        case 1:
            baseCooldownFrames = 20;
            break;

        //shockwave bullet
        case 2:
            baseCooldownFrames = 100;
            break;

        case 3:
            baseCooldownFrames = 120;
            break;

        case 4:
            baseCooldownFrames = 120;
            break;

        case 5:
            baseCooldownFrames = 140;
            break;

        case 6:
            baseCooldownFrames = 160;
            break;

        default:
            baseCooldownFrames = 60; //deafault, shouldnt happen
            break;
        }

        //set bullet to canShoot if the time is right.
        if (frame - cooldownInfo->lastShotFrame > (baseCooldownFrames / this->bulletCooldownMap[bulletID]->firerate) / this->currentFirerate)
        {
            cooldownInfo->canShoot = true;
        }  
    }

    //check if turret shot can be put off cooldown
    // base case: 1 firerate is 1 shot every second

    //       v time from last shot
    //if (frame - this->lastShotFrame > 60 / this->firerate) canShoot = true; //old

    //NEW map is id : BulletCooldownInfo struct, go thorugh each and set the canShoots for each based on lastShot frame and firerate.

}

TurretLaser* Turret::GetLaser()
{
    return this->laser;
}

void Turret::UpdateAngle(int mouseX, int mouseY)
{
    this->angle = CalculateAngle((int)this->position.x, (int)this->position.y, mouseX, mouseY);
}

void Turret::ShootBullet(std::vector<Bullet*>& bullets, int id)
{
    Bullet* b;

    //create a new bullet based on id
    switch (id)
    {
    case 1:
        b = new TurretBullet(this);
        break;

    case 2:
        b = new ShockwaveBullet(this);
        break;

    case 3:
        b = new FireBullet(this);
        break;
    
    case 4:
        b = new SniperBullet(this);
        break;

    case 5:
        b = new LightningBullet(this);
        break;

    case 6:
        b = new BombBullet(this);
        break;

    default: //fallback to turretbbullet on failure
        b = new TurretBullet(this);
        std::cout << "Could not find that bullet id. Shooting TurretBullet.\n";
        break;
    }

    //set its pos and velocity
    b->SetPosition(this->position.x, this->position.y);
    b->SetCurrentVelocity(b->GetBaseSpeed() * this->bulletSpeedMultiplier * cosf(this->angle + GetRandomFloat(-0.02f, 0.02f)), b->GetBaseSpeed() * this->bulletSpeedMultiplier * sinf(this->angle + GetRandomFloat(-0.02f, 0.02f)));

    bullets.push_back(b);
    
    //update this bullet id's cooldowns
    this->bulletCooldownMap[id]->canShoot = false;
    this->bulletCooldownMap[id]->shotThisFrame = true;
}

void Turret::SetBulletSpeedMultiplier(float multiplier)
{
    this->bulletSpeedMultiplier = multiplier;
}

void Turret::SetBaseFirerate(float firerate)
{
    this->baseFirerate = firerate;
}

void Turret::SetRapidFire(unsigned int frames)
{
    this->rapidFireFrames = frames;
}

void Turret::SetFirerate(int id, float firerate)
{
    this->bulletCooldownMap[id]->firerate = firerate;
}

void Turret::SetPosition(int x, int y)
{
    this->position = { (float)x,(float)y };
}

void Turret::SetLaserFrames(unsigned int frames)
{
    this->laserFrames = frames;
}

float Turret::GetCurrentBaseFirerate()
{
    return this->currentFirerate;
}

float Turret::GetFirerate(int id)
{
    return this->bulletCooldownMap[id]->firerate;
}

const std::unordered_map<int, BulletCooldownInfo*>& Turret::GetBulletCooldownMap()
{
    return this->bulletCooldownMap;
}

bool Turret::IsBulletUnlocked(int id)
{
    return this->bulletCooldownMap[id]->unlocked;
}

void Turret::UnlockBullet(int id)
{
    this->bulletCooldownMap[id]->unlocked = true;
}


