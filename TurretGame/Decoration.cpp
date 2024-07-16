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

	//tree
	case 3:
		this->texture = &textures[23];
		this->scale = 3.0f;
		break;


	//cactus1
	case 4:
		this->texture = &textures[40];
		this->scale = 1.0f;
		break;

	//cactus2
	case 5:
		this->texture = &textures[41];
		this->scale = 1.0f;
		break;

	//cactus3
	case 6:
		this->texture = &textures[42];
		this->scale = 1.0f;
		break;

	//pyramid
	case 7:
		this->texture = &textures[43];
		this->scale = 1.0f;
		break;

	//stone1
	case 8:
		this->texture = &textures[44];
		this->scale = 0.7f;
		break;

	//stone2
	case 9:
		this->texture = &textures[45];
		this->scale = 1.0f;
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
