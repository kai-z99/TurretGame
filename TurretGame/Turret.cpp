#include "Turret.h"
#include "raymath.h"
#include "helpers.h"
#include "Projectile.h"

Turret::Turret()
{
    this->angle = 0;

    //Texture init
    this->texture = LoadTexture("turret.png");
    this->textureWidth = this->texture.width;
    this->textureHeight = this->texture.height;
    this->textureSourceRec = { 0.0f, 0.0f, (float)this->textureWidth, (float)this->textureHeight };
    this->textureDestRec = { this->position.x, this->position.y, (float)this->textureWidth, (float)this->textureHeight };
    this->textureRotationPoint = { this->textureWidth / 2.0f, this->textureHeight / 2.0f + 10.0f };

    //gun state
    this->lastShotFrame = 0;
    this->canShoot = true;
    this->shotThisFrame = false;

    //gun settings
    this->baseBulletSpeed = 20.0f;
    this->bulletSpeedMultiplier = 1.0f;
    this->firerate = 1.5f; // in shots per second

}

void Turret::Draw()
{
    DrawTexturePro(this->texture, this->textureSourceRec, this->textureDestRec, this->textureRotationPoint, this->angle * RAD2DEG + 90.0f, WHITE);
}

void Turret::Update(unsigned int frame, int mouseX, int mouseY)
{
    //update its angle
    this->UpdateAngle(mouseX, mouseY);

    if (this->shotThisFrame) // update the last shot frame if the turret shot
    {
        this->lastShotFrame = frame;
        this->shotThisFrame = false;
    }

    //check if turret shot can be put off cooldown
    // base case: 1 firerate is 1 shot every second

    //       v time from last shot
    if (frame - this->lastShotFrame > 60 / this->firerate) canShoot = true;

}

void Turret::UpdateAngle(int mouseX, int mouseY)
{
    this->angle = CalculateAngle(this->position.x, this->position.y, mouseX, mouseY);
}

void Turret::ShootProjectile(std::vector<Projectile*>& projectiles)
{
    Projectile* p = new Projectile();
    p->SetPosition(this->position.x, this->position.y);
    p->SetVelocity(this->baseBulletSpeed * this->bulletSpeedMultiplier * cosf(this->angle), this->baseBulletSpeed * this->bulletSpeedMultiplier * sinf(this->angle));

    projectiles.push_back(p);

    this->shotThisFrame = true; // required to update last shot frame
    this->canShoot = false; // put the turret on cooldown
}

void Turret::SetBulletSpeedMultiplier(float multiplier)
{
    this->bulletSpeedMultiplier = multiplier;
}

float Turret::GetFirerate()
{
    return this->firerate;
}

unsigned int Turret::GetLastShotFrame()
{
    return this->lastShotFrame;
}

bool Turret::GetCanShoot()
{
    return this->canShoot;
}


