#pragma once
#include "raylib.h";

class Decoration
{
public:
	Decoration(int id, int x, int y);

	void Draw();

	Vector2 GetPosition() const;
	void SetPosition(int x, int y);

private:
	Vector2 position;
	Texture2D* texture;
	float scale;
};