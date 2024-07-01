#include "Decoration.h"
#include <iostream>

#include "textures.h"
Decoration::Decoration(int id, int x, int y)
{
	this->position = {(float)x, (float)y};

	switch (id)
	{
	//grass1
	case 0:
		this->texture = &textures[20];
		this->scale = 3.0f;
		break;

	//Grass2
	case 1:
		this->texture = &textures[21];
		this->scale = 3.0f;
		break;

	//bush
	case 2:
		this->texture = &textures[22];
		this->scale = 3.0f;
		break;

	default:
		std::cout << "texture not found, drawing Grass1" << '\n';
		this->texture = &textures[20];
		this->scale = 3.0f;
		break;
	}
}

void Decoration::Draw()
{
	DrawTextureEx(*this->texture, this->position, 0.0f, this->scale, WHITE);
}

Vector2 Decoration::GetPosition() const
{
	return this->position;
}

void Decoration::SetPosition(int x, int y)
{
	this->position.x = (float)x;
	this->position.y = (float)y;
}
