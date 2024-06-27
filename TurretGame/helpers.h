#pragma once
#include "raylib.h"

float CalculateAngle(int x0, int y0, int x1, int y1); // based on 2 points, for position
float CalculateAngle(int x, int y); //based on just x and y;
float GetRandomFloat(float min, float max);
bool CheckCollisionRecLine(Vector2 p1, Vector2 p2, Rectangle rec);
Vector2 RotatePoint(Vector2& v, Vector2 c, float angle);