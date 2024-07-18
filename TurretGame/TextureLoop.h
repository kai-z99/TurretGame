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
	void ToggleReflectedImage();
	void SetTint(Color tint);
	void SetScale(float scale);
	void SetRotation(float rotation);
	void SetAnimationState(int state);
	void SetRotationOffset(float offset);

	Vector2 GetDestDimensions() const;

private:
	int segments;
	int animationState;
	float scale;
	bool mirrored;
	bool reflected;
	float rotation;
	float rotationOffset;
	Color tint;

	Vector2 position;
	Texture2D* texture;
	int textureWidth;
	int textureHeight;
	Rectangle textureSourceRec;
	Rectangle textureDestRec;
	Vector2 textureOriginPoint;

};