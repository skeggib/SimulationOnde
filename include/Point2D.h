#pragma once

#include "Vector2D.h"

class Point2D
{

public:

    double x, y;

    Point2D(double x = 0, double y = 0);
};

Vector2D operator-(const Point2D &p1, const Point2D &p2);
