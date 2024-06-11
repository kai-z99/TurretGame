#include "Turret.h"
#include <iostream>
#include "raymath.h"
#include "types.h"
#include "helpers.h"
#include "TurretBullet.h"
#include "ShockwaveBullet.h"
#include "FireBullet.h"
#include "textures.h" 

Turret::Turret()
{
    this->angle = 0;

    //Texture init
    this->texture = &textures[1];
    this->textureWidth = this->texture->width;
    this->textureHeight = this->texture->height;
    this->textureSourceRec = { 0.0f, 0.0f, (float)this->textureWidth, (float)this->textureHeight };
    this->textureDestRec = { this->position.x, this->position.y, (float)this->textureWidth, (float)this->textureHeight };
    this->textureOriginPoint = { this->textureWidth / 2.0f, this->textureHeight / 2.0f + 10.0f };

    //gun settings
    this->bulletSpeedMultiplier = 1.0f;

    this->baseFirerate = 1.5f; // in shots per second for turretBullet
    this->currentFirerate = this->baseFirerate;
    this->rapidFirerate = this->baseFirerate * 3.0f;
    this->rapidFireFrames = 0;

    this->baseSpecialFirerate = 1.0f;
    this->currentSpecialFirerate = this->baseSpecialFirerate;
    this->rapidSpecialFirerate = this->baseSpecialFirerate * 3.0f;
    this->specialRapidfireFrames = 0;

    
    //initate bullet cooldown map
    for (int i = 1; i <= 3; i++)
    {
        this->bulletCooldownMap[i] = new BulletCooldownInfo();
        this->bulletCooldownMap[i]->canShoot = true;
        this->bulletCooldownMap[i]->lastShotFrame = 0;
        this->bulletCooldownMap[i]->shotThisFrame = false;
    }

    

}

void Turret::Draw()
{
    DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, this->angle * RAD2DEG + 90.0f, WHITE);
}

void Turret::Update(unsigned int frame, int mouseX, int mouseY)
{
    //update its angle
    this->UpdateAngle(mouseX, mouseY);

    if (this->rapidFireFrames > 0)
    {
        this->currentFirerate = this->rapidFirerate;
        this->rapidFireFrames -= 1;
    }
         
    else this->currentFirerate = this->baseFirerate;


    if (this->specialRapidfireFrames > 0)
    {
        this->currentSpecialFirerate = this->rapidSpecialFirerate;
        this->specialRapidfireFrames -= 1;
    }

    else this->currentSpecialFirerate = this->baseSpecialFirerate;


    //update bullet cooldowns

    //go through each bullet type
    for (auto& pair : this->bulletCooldownMap)
    {
        //if this was the frame it shot, update its last shot frame.
        if (pair.second->shotThisFrame)
        {
            pair.second->lastShotFrame = frame;
            pair.second->shotThisFrame = false;
        }

        //check if bullet can be put off cooldown based on its last shot frame

        //check bullet id 1 (TurretBullet)
        if (pair.first == 1) 
        {
            //if its been long enough. set canShoot to be true in its BulletCooldownInfo.
            if (frame - pair.second->lastShotFrame > 60 / this->currentFirerate) pair.second->canShoot = true;
        }

        //shockwave bullet
        else if (pair.first == 2) //not affected by firerate rn, figure a cool implelention maybe
        {
            if (frame - pair.second->lastShotFrame > 150 / this->currentSpecialFirerate) pair.second->canShoot = true;
        }

        //Firebullet
        else if (pair.first == 3) //not affected by firerate rn, figure a cool implelention maybe
        {
            if (frame - pair.second->lastShotFrame > 180 / this->currentSpecialFirerate) pair.second->canShoot = true;
        }
        
    }

    //check if turret shot can be put off cooldown
    // base case: 1 firerate is 1 shot every second

    //       v time from last shot
    //if (frame - this->lastShotFrame > 60 / this->firerate) canShoot = true; //old

    //NEW map is id : BulletCooldownInfo struct, go thorugh each and set the canShoots for each based on lastShot frame and firerate.

}

void Turret::UpdateAngle(int mouseX, int mouseY)
{
    this->angle = CalculateAngle(this->position.x, this->position.y, mouseX, mouseY);
}

void Turret::ShootBullet(std::vector<Bullet*>& bullets, int id)
{
    Bullet* b;

    //create a new bullet based on id
    switch (id)
    {
    case 1:
        b = new TurretBullet();
        break;

    case 2:
        b = new ShockwaveBullet();
        break;

    case 3:
        b = new FireBullet();
        break;

    default: //fallback to turretbbullet on failure
        b = new TurretBullet();
        std::cout << "Could not find that bullet id. Shooting TurretBullet.\n";
        break;
    }

    //set its pos and velocity
    b->SetPosition(this->position.x, this->position.y);
    b->SetVelocity(b->GetBaseSpeed() * this->bulletSpeedMultiplier * cosf(this->angle), b->GetBaseSpeed() * this->bulletSpeedMultiplier * sinf(this->angle));

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
    this->rapidFireFrames += frames;
}

void Turret::SetSpecialRapidfire(unsigned int frames)
{
    this->specialRapidfireFrames += frames;
}

void Turret::SetBaseSpecialFirerate(float firerate)
{
    this->baseSpecialFirerate = firerate;
}

float Turret::GetCurrentFirerate()
{
    return this->currentFirerate;
}

const std::unordered_map<int, BulletCooldownInfo*>& Turret::GetBulletCooldownMap()
{
    return this->bulletCooldownMap;
}


