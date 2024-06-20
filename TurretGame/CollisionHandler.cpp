#include "CollisionHandler.h"
#include "Game.h"

#include "VisualEffectsManager.h"

#include "Bullet.h"

#include "AreaEffect.h"
#include "BombExplosion.h"
#include "IceSheet.h"

#include "Enemy.h"
#include "RedKoopaEnemy.h"


CollisionHandler::CollisionHandler(Game* game)
{
	this->game = game;
}

void CollisionHandler::HandleEnemyCollisions()
{
	//bullet collisions
	for (Bullet* b : this->game->bullets)
	{
		if (b->isActive)
		{
			for (Enemy* e : this->game->enemies)
			{
				if (e->isActive && b->EnemyCollided(e)) //if collide, remove buullet and deal damage
				{
					this->HandleBulletToEnemy(b, e);
				}

			}
		}
	}

	//AOE collisions
	for (AreaEffect* a : this->game->areaEffects)
	{
		if (a->isActive)
		{
			this->HandleAOEToEnemies(a);
		}
	}

}

void CollisionHandler::HandleBulletToEnemy(Bullet* b, Enemy* e)
{
	//display the explosion
	this->game->effectManager->DisplayExplosion(b->GetPosition());

	//DAMAGE AND KNOCKBACK
	switch (e->GetID())
	{
		//RED KOOPA
	case 3:
		//only apply dmg and kb if not in shell
		if (dynamic_cast<RedKoopaEnemy*>(e)->shellForm) break;

	default:
		e->SetHealth(e->GetHealth() - b->GetBaseDamage());
		e->ApplyKnockback(b);
		break;

	}

	//STATUS EFFECT
	switch (b->GetID())
	{
		// fire bullet
	case 3:
		//apply burning for 4 seconds if not a red koopa
		if (e->GetID() != 3)
		{
			e->ApplyStatusEffect(Burning, 240);
			break;
		}

		//dont apply burn if red koopa in shell
		else if (!dynamic_cast<RedKoopaEnemy*>(e)->shellForm)
		{
			e->ApplyStatusEffect(Burning, 240);
		}
		break;

	default:
		break;
	}

	b->isActive = false;
}

//prereq: a isActive
void CollisionHandler::HandleAOEToEnemies(AreaEffect* a)
{
	switch (a->GetID())
	{
	//BOMB EXPLOSTION
	case 1:
		for (Enemy* e : this->game->enemies)
		{
			if (e->isActive)
			{
				BombExplosion* exp = dynamic_cast<BombExplosion*>(a);
				if (exp->isDetonateFrame && exp->EnemyCollided(e))
				{
					e->SetHealth(e->GetHealth() - exp->GetDamage());
					e->ApplyKnockback(exp->GetKnockbackFrames());
				}
			}	
		}
		break;

	//ice sheet
	case 2:
		for (Enemy* e : this->game->enemies)
		{
			if (e->isActive)
			{
				IceSheet* i = dynamic_cast<IceSheet*>(a);
				if (i->EnemyCollided(e))
				{
					//id 3 is red koopa
					if (e->GetID() != 3) e->ApplyStatusEffect(Chilled, 150);
					//only chill when its not in shell
					else if (!dynamic_cast<RedKoopaEnemy*>(e)->shellForm) e->ApplyStatusEffect(Chilled, 150);
				}
			}
		}
		break;

	default:
		break;
	}
}


