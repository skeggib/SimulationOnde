#include "Coordinates.h"

Coordinates::Coordinates(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

std::ostream& operator<<(std::ostream& os, const Coordinates& coord)
{
    os << '(' << coord.x << ", " << coord.y << ", " << coord.z << ')';
    return os;
}
