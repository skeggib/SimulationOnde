#pragma once

#include "Coordinates.h"
#include "Vector.h"

class Point : public Coordinates
{

    public:

        Point(double x = 0, double y = 0, double z = 0);

        //void translate(const Vector &);
        //static double distance(Point p1, Point p2);
};

Point operator+(const Point &p, const Vector &v);
