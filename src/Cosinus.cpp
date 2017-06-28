#include "Cosinus.h"

Cosinus::Cosinus(int values)
{
    for (int i = 0; i < values; i++)
    {
        _values.push_back(std::cos((double)i / (double)values * 2.0 * M_PI));
    }
}

double Cosinus::cos(double x) const
{
	x = std::fmod(x, 2.0 * M_PI);
	if (x < 0)
		x += 2.0 * M_PI;
    int index = (int)((double)_values.size() * x / (2.0 * M_PI));
	return _values[index];
	return 0;
}
