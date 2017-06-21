#pragma once

#include <ostream>

class Coordinates
{
    public:

        double x, y, z;
        Coordinates(double x, double y, double z);
};

std::ostream& operator<<(std::ostream& os, const Coordinates& coord);
