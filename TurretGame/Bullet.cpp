#include "Bullet.h"
#include "raylib.h"
#include "Enemy.h"
#include "constants.h"
#include "helpers.h"

void Bullet::Draw() //default draw is a red circle hitbox; debug only
{
    DrawCircleLines((int)this->position.x, (int)this->position.y, this->hitBoxRadius, RED); //temp
}

void Bullet::Update(unsigned int frame)
{
    Projectile::Update(frame);

    //check if its off the screen
    if (this->position.x > screenWidth + 200 || this->position.x < -200 || this->position.y > screenHeight + 200 || this->position.y < menuBoundaryY - 200)
    {
        this->isActive = false;
    } 

    //update the angle of the bullet based on velocity
    this->angle = CalculateAngle((int)this->currentVelocity.x, (int)this->currentVelocity.y);
}

bool Bullet::EnemyCollided(Enemy* e)
{
    return CheckCollisionCircleRec(this->position, this->hitBoxRadius, e->GetHitbox()) && e->isActive;
}

float Bullet::GetBaseSpeed() const
{
    return this->baseSpeed;
}

float Bullet::GetBaseDamage() const
{
    return this->baseDamage;
}

int Bullet::GetBaseKnockbackDuration() const
{
    return this->baseKnockbackDuration;
}

int Bullet::GetID() const
{
    return this->id;
}

Turret* Bullet::GetOwner() const
{
    return this->owner;
}

//bool Bullet::IsActive()
//{
//    return this->isActive;
//}
