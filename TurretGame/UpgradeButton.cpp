#include "UpgradeButton.h"

#include <string>

#include "textures.h"

const int UpgradeButton::width = 80;
const int UpgradeButton::height = 80;

UpgradeButton::UpgradeButton(int posX, int posY, Upgrade upgrade)
{
	this->position = { (float)posX, (float)posY };
	this->texture = texture;
	this->upgrade = upgrade;
	this->price = -1;

	switch (this->upgrade)
	{
	case TurretBulletU:
		this->texture = &textures[28];
		break;

	case ShockwaveBulletU:
		this->texture = &textures[7];
		break;

	case FireBulletU:
		this->texture = &textures[18];
		break;

	case SniperBulletU:
		this->texture = &textures[19];
		break;
	
	case LightningBulletU:
		this->texture = &textures[27];
		break;

	case BombBulletU:
		this->texture = &textures[2];
		break;

	case RapidfireU:
		this->texture = &textures[10];
		break;
		
	case LaserU:
		this->texture = &textures[12];
		break;

	case IceU:
		this->texture = &textures[15];
		break;

	case ExplosiveU:
		this->texture = &textures[13];
		break;

	case CloneU:
		this->texture = &textures[30];
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
	Rectangle source = { 0.0f, 0.0f, (float)this->texture->width, (float)this->texture->height };
	Rectangle dest = { this->position.x, this->position.y, (float)UpgradeButton::width, (float)UpgradeButton::height };
	Vector2 origin = { (float)UpgradeButton::width / 2.0f, (float)UpgradeButton::height / 2.0f };

	DrawTexturePro(*this->texture, source, dest, origin, 0.0f, tint);

	//std::string text = std::to_string(this->price) + " C";
	//int width = MeasureText(text.c_str(), 30);
	//DrawText(text.c_str(), (int)this->position.x - width / 2, (int)this->position.y - 90, 30, BLUE);
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
	Rectangle rec = { this->position.x - (UpgradeButton::width / 2), this->position.y - (UpgradeButton::height / 2), UpgradeButton::width, UpgradeButton::height};
	return CheckCollisionPointRec({(float)mouseX, (float)mouseY}, rec);
}
