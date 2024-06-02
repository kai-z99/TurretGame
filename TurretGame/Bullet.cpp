#include "Bullet.h"

void Bullet::Draw() //default draw is a red circle; debug only
{
    DrawCircle(this->position.x, this->position.y, 10, RED); //temp
}

bool Bullet::EnemyCollided(Enemy* e)
{
    return false;
}

float Bullet::GetBaseSpeed() const
{
    return this->baseSpeed;
}
