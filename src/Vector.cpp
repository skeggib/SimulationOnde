#include "Vector.h"

Vector::Vector(double x, double y, double z)
: Coordinates(x, y, z) { }

/*Vector::Vector(Point p1, Point p2)
{
    x = p2.x - p1.x;
    y = p2.y - p1.y;
    z = p2.z - p1.z;
}*/

double Vector::norm()
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Vector Vector::integral(double delta_t)
{
    Vector res;

    res.x = delta_t * x;
    res.y = delta_t * y;
    res.z = delta_t * z;

    return res;
}

void Vector::operator+=(const Vector &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
}

Vector operator+(const Vector &v1, const Vector &v2)
{
    Vector res = v1;

    res.x += v2.x;
    res.y += v2.y;
    res.z += v2.z;

    return res;
}

Vector operator-(const Vector &v)
{
    Vector res;

    res.x = -v.x;
    res.y = -v.y;
    res.z = -v.z;

    return res;
}

Vector operator-(const Vector &v1, const Vector &v2)
{
    return -v2 + v1;
}

Vector operator*(const double &k, const Vector &v)
{
    Vector res = v;

    res.x *= k;
    res.y *= k;
    res.z *= k;

    return res;
}

// Scalar product
double operator*(const Vector &v1, const Vector &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Vector product
Vector operator^(const Vector &v1, const Vector &v2)
{
    Vector res;

    res.x = v1.y * v2.z - v1.z * v2.y;
    res.y = v1.z * v2.x - v1.x * v2.z;
    res.z = v1.x * v2.y - v1.y * v2.x;

    return res;
}
