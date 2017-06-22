#pragma once

#include <cmath>

#include "Form.h"
#include "Point.h"
#include "Vector.h"

class Triangle : public Form
{

private:

    Point _origin;
    Vector _v1;
    Vector _v2;

public:

    Triangle(Point origin, Vector v1, Vector v2);
    Triangle(Point origin, Point p1, Point p2);

    void render();
    void update(double delta_t);
};
