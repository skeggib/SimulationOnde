#pragma once

#include <cmath>

class Wave
{

private:

    double _a;
    double _f;
    double _c;

public:

    Wave(double a = 1, double f = 1, double c = 1);

    double getIntensity(double r, double t);
};
