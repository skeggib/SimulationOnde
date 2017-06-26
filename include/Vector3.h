#pragma once

#include <cmath>

class Vector3
{
public:

	double x, y, z;

    // Instantiates a Vector from its coordinates
    Vector3(double x = 0, double y = 0, double z = 0);

    // Or with two points
    //Vector(Point p1, Point p2);

    // Compute the vector norm
    double norm();

    Vector3 integral(double delta_t);

    // Overloaded standard operators
    void operator+=(const Vector3 &v);
};

Vector3 operator+(const Vector3 &v1, const Vector3 &v2);
Vector3 operator-(const Vector3 &v);
Vector3 operator-(const Vector3 &v1, const Vector3 &v2);
Vector3 operator*(const double &k, const Vector3 &v);
// Scalar product
double operator*(const Vector3 &v1, const Vector3 &v2);
// Vector product
Vector3 operator^(const Vector3 &v1, const Vector3 &v2);
