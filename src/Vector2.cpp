#include "Vector2.h"

Vector2::Vector2(double x, double y) :
    x(x), y(y)
{

}

double Vector2::norm()
{
    return sqrt(x*x + y*y);
}

const Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(
		lhs.x - rhs.x,
		lhs.y - rhs.y);
}