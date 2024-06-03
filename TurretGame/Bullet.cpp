#include "Bullet.h"
#include "raylib.h"
#include "Enemy.h"
#include "constants.h"

void Bullet::Draw() //default draw is a red circle hitbox; debug only
{
    DrawCircleLines(this->position.x, this->position.y, this->hitBoxRadius, RED); //temp
}

void Bullet::Update()
{
    Projectile::Update();

    //check if its off the screen
    if (this->position.x > screenWidth + 200 || this->position.x < -200 || this->position.y > screenHeight + 200 || this->position.y < menuBoundaryY - 200)
    {
        this->isActive = false;
    } 
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

//bool Bullet::IsActive()
//{
//    return this->isActive;
//}
