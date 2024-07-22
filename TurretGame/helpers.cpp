#include "helpers.h"
#include "raymath.h"


float CalculateAngle(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    if (dy == 0) return 0; // handle zero division

    float angle = atanf((float)dy / (float)dx);

    if (dx < 0.0f) return angle + PI;
    return angle;
}

//in a vaccuum
float CalculateAngle(int x, int y)
{
    if (y == 0) return 0; // handle zero division

    float angle = atanf((float)y / (float)x);

    if (x < 0.0f) return angle + PI;
    return angle;
}

float GetRandomFloat(float min, float max) {
    int intMin = 0;
    int intMax = 10000;  // This determines the precision

    int randomInt = GetRandomValue(intMin, intMax);

    //range is [0, 1]
    float randomFloat = static_cast<float>(randomInt) / intMax;

    return min + randomFloat * (max - min);
}

bool CheckCollisionRecLine(Vector2 p1, Vector2 p2, Rectangle rec)
{
    //origin to top right
    if (CheckCollisionLines(p1, p2, { rec.x, rec.y }, { rec.x + rec.width, rec.y }, nullptr)) return true;

    //top right to bot right
    if (CheckCollisionLines(p1, p2, { rec.x + rec.width, rec.y }, { rec.x + rec.width, rec.y + rec.height }, nullptr)) return true;

    //bot right to bot left
    if (CheckCollisionLines(p1, p2, { rec.x + rec.width, rec.y + rec.height }, { rec.x, rec.y + rec.height }, nullptr)) return true;

    //bot left to origin
    if (CheckCollisionLines(p1, p2, { rec.x, rec.y + rec.height }, { rec.x, rec.y }, nullptr)) return true;

    return false;
}

Vector2 RotatePoint(Vector2& v, Vector2 c, float angle)
{
    float tc = cosf(angle);
    float ts = sinf(angle);
    float x_rotated = ((v.x - c.x) * tc) - ((c.y - v.y) * ts) + c.x;
    float y_rotated = -c.y + ((c.y - v.y) * tc) + ((v.x - c.x) * ts);

    return { x_rotated , -y_rotated };
}

Color RotateColorChannels(Color color)
{
    Color newColor = color;

    unsigned char rTg = color.r;
    unsigned char gTb = color.g;
    unsigned char bTr = color.b;

    newColor.r = bTr;
    newColor.g = rTg;
    newColor.b = gTb;

    return newColor;
}
