#include "Wave.h"

Wave::Wave(double a, double f, double c, Point2D source) :
    _a(a),
    _f(f),
    _c(c)
{
    _source = source;
}

double porte(double t)
{
    if (t < -1/2)
        return 0;
    if (t > 1/2)
        return 0;
    return 1;
}

double Wave::getIntensity(Point2D p, double t)
{
    Vector2D dist = p - _source;
    double r = dist.norm();
    double b = 0.5;

    //double lambda = _c / _f;

    return _a * cos(2*M_PI*_f * (r/_c - t)) * exp(-b * r);
}
