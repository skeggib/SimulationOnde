#include "Vector2D.h"

Vector2D::Vector2D(double x, double y) :
    x(x), y(y)
{

}

double Vector2D::norm()
{
    return sqrt(x*x + y*y);
}
