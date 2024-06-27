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
	Rectangle source = { 0.0f, 0.0f, this->texture->width, this->texture->height };
	Rectangle dest = { this->position.x, this->position.y, UpgradeButton::width, UpgradeButton::height };
	Vector2 origin = { (float)UpgradeButton::width / 2.0f, (float)UpgradeButton::height / 2.0f };

	DrawTexturePro(*this->texture, source, dest, origin, 0.0f, tint);

	std::string text = std::to_string(this->price) + " Coins";
	int width = MeasureText(text.c_str(), 30);
	DrawText(text.c_str(), (int)this->position.x - width / 2, (int)this->position.y - 90, 30, BLUE);
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
