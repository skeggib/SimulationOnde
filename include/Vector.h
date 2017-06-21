#pragma once

#include <cmath>

#include "Coordinates.h"
#include "Point.h"

class Vector : public Coordinates
{
public:

    // Instantiates a Vector from its coordinates
    Vector(double x = 0, double y = 0, double z = 0);

    // Or with two points
    //Vector(Point p1, Point p2);

    // Compute the vector norm
    double norm();

    Vector integral(double delta_t);

    // Overloaded standard operators
    void operator+=(const Vector &v);
};

Vector operator+(const Vector &v1, const Vector &v2);
Vector operator-(const Vector &v);
Vector operator-(const Vector &v1, const Vector &v2);
Vector operator*(const double &k, const Vector &v);
// Scalar product
double operator*(const Vector &v1, const Vector &v2);
// Vector product
Vector operator^(const Vector &v1, const Vector &v2);
