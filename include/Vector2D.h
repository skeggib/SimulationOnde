#pragma once

#include <cmath>

class Vector2D
{
public:

    double x, y;

    Vector2D(double x = 0, double y = 0);

    double norm();
};
