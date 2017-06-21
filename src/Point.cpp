#include "Point.h"

Point::Point(double x, double y, double z)
: Coordinates(x, y, z) {}

/*void Point::translate(const Vector &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
}*/

/*double Point::distance(Point p1, Point p2)
{
    Vector vect(p1, p2);

    return vect.norm();
}*/

Point operator+(const Point &p, const Vector &v)
{
    return Point(p.x + v.x, p.y + v.y, p.z + v.z);
}
