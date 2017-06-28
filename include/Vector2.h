#pragma once

#include <cmath>

class Vector2
{
public:

    double x, y;

    Vector2(double x = 0, double y = 0);

    double norm();
};

const Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
const Vector2 operator-(const Vector2& lhs, const Vector2& rhs);

const Vector2 operator*(const double& lhs, const Vector2& rhs);
const Vector2 operator*(const Vector2& lhs, const double& rhs);

// Scalar product
double operator*(const Vector2 &v1, const Vector2 &v2);