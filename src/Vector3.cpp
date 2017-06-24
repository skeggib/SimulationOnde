#include "Vector3.h"

Vector3::Vector3(double x, double y, double z) :
	x(x),
	y(y),
	z(z)
{

}

double Vector3::norm()
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Vector3 Vector3::integral(double delta_t)
{
    Vector3 res;

    res.x = delta_t * x;
    res.y = delta_t * y;
    res.z = delta_t * z;

    return res;
}

void Vector3::operator+=(const Vector3 &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
}

Vector3 operator+(const Vector3 &v1, const Vector3 &v2)
{
    Vector3 res = v1;

    res.x += v2.x;
    res.y += v2.y;
    res.z += v2.z;

    return res;
}

Vector3 operator-(const Vector3 &v)
{
    Vector3 res;

    res.x = -v.x;
    res.y = -v.y;
    res.z = -v.z;

    return res;
}

Vector3 operator-(const Vector3 &v1, const Vector3 &v2)
{
    return -v2 + v1;
}

Vector3 operator*(const double &k, const Vector3 &v)
{
    Vector3 res = v;

    res.x *= k;
    res.y *= k;
    res.z *= k;

    return res;
}

// Scalar product
double operator*(const Vector3 &v1, const Vector3 &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Vector product
Vector3 operator^(const Vector3 &v1, const Vector3 &v2)
{
    Vector3 res;

    res.x = v1.y * v2.z - v1.z * v2.y;
    res.y = v1.z * v2.x - v1.x * v2.z;
    res.z = v1.x * v2.y - v1.y * v2.x;

    return res;
}
