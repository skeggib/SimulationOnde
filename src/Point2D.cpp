#include "Point2D.h"

Point2D::Point2D(double x, double y) :
    x(x), y(y)
{

}

Vector2D operator-(const Point2D &p1, const Point2D &p2)
{
    return Vector2D(p1.x - p2.x, p1.y - p2.y);
}
