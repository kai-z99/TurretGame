#include "Sentry.h"

#include "Enemy.h"
#include "Bullet.h"

#include "helpers.h"



float Sentry::damageMultiplier = 0.5f;
int Sentry::duration = 500;

Sentry::Sentry()
{
	this->targetMode = 0;
	this->target = nullptr;

	this->main = false; // main is the main turret only not sentry
}

void Sentry::Update(unsigned int frame, int mouseX, int mouseY, std::vector<Enemy*>& enemies, std::vector<Bullet*>& bullets)
{
	Turret::Update(frame, mouseX, mouseY);
	
	//IF THE TARGET IS NULL, AIM THE TURRET FWD. IF ITS NOT, AIM AT THE ENEMY.

	if (enemies.size() > 0)
	{
		//first, set an initial target. if there is no active enemiues, set target to nullptr.
		for (Enemy*& e : enemies)
		{
			if (e->isActive)
			{
				this->target = e;
				break;
			}
		}

		//if there is atleasst one active enemy, find the target.
		if (this->target != nullptr)
		{
			for (Enemy*& e : enemies)
			{
				if (targetMode == 0) //closest
				{
					if (e->isActive && e->GetPosition().x < this->target->GetPosition().x)
					{
						this->target = e;
					}
				}

				else //strongest
				{
					if (e->isActive && e->GetHealth() > this->target->GetHealth())
					{
						this->target = e;
					}
				}

			}
		}	
	}

	else
	{
		this->target = nullptr;
	}

	//now that the target is set, update the angle to face it.
	if (this->target != nullptr)
	{
		this->angle = CalculateAngle((int)this->position.x, (int)this->position.y, (int)target->GetPosition().x, (int)target->GetPosition().y);
	}

	//if no target exists, just face fwd.
	else
	{
		this->angle = 0.0f;
	}	

	for (const auto& cooldown : this->GetBulletCooldownMap()) // bulletid : cooldownInfo
	{
		//if that type isnt on cooldown
		if (cooldown.second->canShoot)
		{
			//shoot that bullet type once.
			this->ShootBullet(bullets, cooldown.first);
		}
	}
}

void Sentry::SetTargetMode(int mode)
{
	this->targetMode = mode;
}

