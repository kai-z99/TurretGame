#include "CollisionHandler.h"
#include "Game.h"

#include "VisualEffectsManager.h"

#include "Bullet.h"
#include "TurretLaser.h"
#include "Turret.h"

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
	Game* g = this->game;
	//bullet collisions
	for (Bullet* b : g->bullets)
	{
		if (b->isActive)
		{
			for (Enemy* e : g->enemies)
			{
				if (e->isActive && b->EnemyCollided(e)) //if collide, remove buullet and deal damage
				{
					this->HandleBulletToEnemy(b, e);
				}

			}
		}
	}

	//AOE collisions
	for (AreaEffect* a : g->areaEffects)
	{
		if (a->isActive)
		{
			this->HandleAOEToEnemies(a);
		}
	}

	//laser
	if (g->turret->GetLaser()->isActive) this->HandleLaserToEnemies(g->turret->GetLaser());
	
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

	//sniper
	case 4:
		//chill breifly, append to not cut ice sheet short
		if (e->GetID() != 3)
		{
			e->AppendStatusEffect(Chilled, 20);
			break;
		}

		//dont apply burn if red koopa in shell
		else if (!dynamic_cast<RedKoopaEnemy*>(e)->shellForm)
		{
			e->AppendStatusEffect(Chilled, 20);
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
					e->SetHealth(e->GetHealth() - BombExplosion::damage);
					e->ApplyKnockback(BombExplosion::knockbackFrames);
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
					if (e->GetID() != 3) e->ApplyStatusEffect(Chilled, IceSheet::intensity);
					//only chill when its not in shell
					else if (!dynamic_cast<RedKoopaEnemy*>(e)->shellForm) e->ApplyStatusEffect(Chilled, IceSheet::intensity);
				}
			}
		}
		break;

	default:
		break;
	}
}

void CollisionHandler::HandleLaserToEnemies(TurretLaser* laser)
{
	for (Enemy* e : this->game->enemies)
	{
		if (laser->isCollide(e) && laser->isDamageFrame)
		{
			e->SetHealth(e->GetHealth() - TurretLaser::damage);
		}
	}

}


