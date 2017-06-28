#include "Wave.h"

Wave::Wave(double a, double f, double c) :
    _a(a),
    _f(f),
    _c(c)
{

}

double porte(double t)
{
    if (t < -1/2)
        return 0;
    if (t > 1/2)
        return 0;
    return 1;
}

double Wave::getIntensity(double r, double t)
{
    double b = 0.2;

    //if (r > _a / b)
    //    return 0;

    double lambda = _c / _f;

    return (_a * cos(2*M_PI*_f * (r/_c - t)));
        //+ b * cos(2*M_PI*_f * (r/_c - t) - M_PI) * r);
}
