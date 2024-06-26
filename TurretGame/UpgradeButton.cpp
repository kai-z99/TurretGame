#include "UpgradeButton.h"

#include <string>

#include "textures.h"

UpgradeButton::UpgradeButton(int posX, int posY, Upgrade upgrade)
{
	this->position = { (float)posX, (float)posY };
	this->texture = texture;
	this->upgrade = upgrade;
	this->price = -1;

	switch (this->upgrade)
	{
	case TurretBulletU:
		this->texture = &textures[2];
		break;

	case ShockwaveBulletU:
		this->texture = &textures[7];
		break;

	case FireBulletU:
		this->texture = &textures[2];
		break;

	case SniperBulletU:
		this->texture = &textures[2];
		break;

	case RapidfireU:
		this->texture = &textures[10];
		break;
		
	case SpecialRapidfireU:
		this->texture = &textures[12];
		break;

	case IceU:
		this->texture = &textures[15];
		break;

	case ExplosiveU:
		this->texture = &textures[13];
		break;
	}
	//temp
}

void UpgradeButton::Draw()
{
	Color tint;

	if (this->isHovering) tint = BLUE;
	else if (this->isHeld) tint = RED;
	else tint = WHITE;

	//temp
	if (this->upgrade == FireBulletU) tint = RED;
	if (this->upgrade == SniperBulletU) tint = BLUE;

	//temp
	DrawTextureEx(*this->texture, this->position, 0.0f, 1.0f, tint);
	DrawRectangleLines(this->position.x, this->position.y, this->texture->width, this->texture->height, RED);
	DrawText(std::to_string(this->price).c_str(), (int)this->position.x, (int)this->position.y - 20, 30, BLUE);
}

void UpgradeButton::Update(int mouseX, int mouseY)
{
	Button::Update(mouseX, mouseY);
}

Upgrade UpgradeButton::GetUpgrade() const
{
	return this->upgrade;
}

int UpgradeButton::GetPrice() const
{
	return this->price;
}

void UpgradeButton::SetPrice(int price)
{
	this->price = price;
}

bool UpgradeButton::MouseCollide(int mouseX, int mouseY)
{
	Rectangle rec = { this->position.x, this->position.y, this->texture->width, this->texture->height };
	return CheckCollisionPointRec({(float)mouseX, (float)mouseY}, rec);
}
