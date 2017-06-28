#include "Vector2.h"

Vector2::Vector2(double x, double y) :
    x(x), y(y)
{

}

double Vector2::norm()
{
    return sqrt(x*x + y*y);
}

const Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(
		lhs.x + rhs.x,
		lhs.y + rhs.y);
}

const Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(
		lhs.x - rhs.x,
		lhs.y - rhs.y);
}

const Vector2 operator*(const double & lhs, const Vector2 & rhs)
{
	return Vector2(rhs.x * lhs, rhs.y * lhs);
}

const Vector2 operator*(const Vector2 & lhs, const double & rhs)
{
	return Vector2(lhs.x * rhs, lhs.y * rhs);
}

double operator*(const Vector2 & v1, const Vector2 & v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}
