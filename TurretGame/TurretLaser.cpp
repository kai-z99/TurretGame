#include "TurretLaser.h"

#include "helpers.h"

#include "Turret.h"
#include "Enemy.h"

int TurretLaser::damage = 1;
int TurretLaser::duration = 100;
Color TurretLaser::color = RED;

TurretLaser::TurretLaser(Turret* t)
{
	this->owner = t;
	this->isActive = false;
	this->isDamageFrame = true;
	this->p1 = t->position;
	this->p2 = { t->position.x + this->length, t->position.y };
	this->angle = t->angle;
	this->thickness = 10.0f;
}

void TurretLaser::Update(unsigned int frame)
{
	//update angle
	this->angle = this->owner->angle;

	//update the angle of the laser
	Vector2 ref = { this->owner->position.x + this->length, this->owner->position.y }; //a line pointing from turret straight right for 2000.0f
	this->p2 = RotatePoint(ref, this->p1, -this->angle);
	
	this->thickness = 10.0f * (abs(sinf(frame * 0.05f)) + 0.2f);

	if (frame % 20 == 0) this->isDamageFrame = true;
	else this->isDamageFrame = false;
}


void TurretLaser::Draw()
{
	DrawLineEx(this->p1, this->p2, this->thickness, this->color);
}

bool TurretLaser::isCollide(Enemy* e)
{
	return CheckCollisionRecLine(this->p1, this->p2, e->GetHitbox());
}




