#include "TextureLoop.h"

TextureLoop::TextureLoop(Texture2D* texture, int segments, float scale, Vector2 position)
{
	this->position = position;
	this->scale = scale;
	this->segments = segments;
	this->mirrored = false;
	this->reflected = false;
	this->rotation = 0.0f;
	this->rotationOffset = 0.0f;
	this->tint = WHITE;
	this->animationState = 1;

	this->texture = texture;
	this->textureWidth = this->texture->width;
	this->textureHeight = this->texture->height;
	this->textureSourceRec = { 0.0f, 0.0f, ((float)this->textureWidth / segments), (float)this->textureHeight }; //first segment of image
	this->textureDestRec = { this->position.x, this->position.y, ((float)this->textureWidth / segments) * this->scale, (float)this->textureHeight * this->scale}; //make sure to scale the image
	this->textureOriginPoint = { (this->textureWidth * this->scale / segments / 2.0f) , this->textureHeight * this->scale / 2.0f }; //middle of image segment
}

void TextureLoop::SetPosition(int x, int y)
{
	this->position.x = (float)x;
	this->position.y = (float)y;
}

void TextureLoop::ToggleMirrorImage()
{
	if (!this->mirrored) this->mirrored = true;
	else this->mirrored = false;
}

void TextureLoop::ToggleReflectedImage()
{
	if (!this->reflected) this->reflected = true;
	else this->reflected = false;
}

void TextureLoop::SetTint(Color tint)
{
	this->tint = tint;
}

void TextureLoop::SetScale(float scale)
{
	this->scale = scale;
}

void TextureLoop::SetRotation(float rotation)
{
	this->rotation = rotation;
}

void TextureLoop::SetAnimationState(int state)
{
	this->animationState = state;
}

void TextureLoop::SetRotationOffset(float offset)
{
	this->rotationOffset = offset;
}

Vector2 TextureLoop::GetDestDimensions() const
{
	return { this->textureDestRec.width, this->textureDestRec.height};
}

void TextureLoop::Update()
{
	//update part of picture we want to show based off anim state
	this->textureSourceRec = { ((float)this->textureWidth / segments) * (this->animationState - 1), //x0
								0.0f,																//y0
								((float)this->textureWidth / segments),								//x1
								(float)this->textureHeight };										//y1

	//mirror/reflect the image
	if (this->mirrored) this->textureSourceRec.width = -this->textureSourceRec.width;
	if (this->reflected) this->textureSourceRec.height = -this->textureSourceRec.height;
	
	//update the destination rectangle
	this->textureDestRec = { this->position.x, this->position.y, ((float)this->textureWidth / segments) * this->scale, (float)this->textureHeight * this->scale };
}

void TextureLoop::Draw()
{
	DrawTexturePro(*this->texture, this->textureSourceRec, this->textureDestRec, this->textureOriginPoint, this->rotation + this->rotationOffset, this->tint);
}

void TextureLoop::NextFrame()
{
	if (this->animationState >= this->segments) this->animationState = 1;
	else this->animationState++;
}


