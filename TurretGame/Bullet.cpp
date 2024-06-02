#include "Bullet.h"
#include "raylib.h"
#include "Enemy.h"

void Bullet::Draw() //default draw is a red circle; debug only
{
    DrawCircle(this->position.x, this->position.y, 10, RED); //temp
}

bool Bullet::EnemyCollided(Enemy* e)
{
    return CheckCollisionCircleRec(this->position, this->hitBoxRadius, e->GetHitbox()) && e->IsActive();
}

float Bullet::GetBaseSpeed() const
{
    return this->baseSpeed;
}

//bool Bullet::IsActive()
//{
//    return this->isActive;
//}
