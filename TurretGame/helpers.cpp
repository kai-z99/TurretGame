#include "helpers.h"
#include "raylib.h"
#include "raymath.h"


float CalculateAngle(int x0, int y0, int x1, int y1)
{
    float dx = x1 - x0;
    float dy = y1 - y0;

    if (dy == 0) return 0; // handle zero division

    float angle = atanf(dy / dx);

    if (dx < 0.0f) return angle + PI;
    return angle;
}

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
