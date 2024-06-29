#pragma once
#include "raylib.h"

class TextureLoop
{
public:
	TextureLoop(Texture2D* texture, int segments, float scale, Vector2 position);
	void Draw();
	void NextFrame();
	void Update();
	void SetPosition(int x, int y);
	void ToggleMirrorImage();
	void SetTint(Color tint);
	void SetScale(float scale);

private:
	int segments;
	int animationState;
	float scale;
	bool mirrored;
	Color tint;

	Vector2 position;
	Texture2D* texture;
	int textureWidth;
	int textureHeight;
	Rectangle textureSourceRec;
	Rectangle textureDestRec;
	Vector2 textureOriginPoint;

};