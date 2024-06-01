#include "helpers.h"
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
