#pragma once

#include <cmath>

#include "Point2D.h"

class Wave
{

private:

    double _a;
    double _f;
    double _c;

    Point2D _source;

public:

    Wave(double a = 1, double f = 1, double c = 1, Point2D source = Point2D());

    double getIntensity(Point2D p, double t);
};
