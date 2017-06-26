#include "Wave.h"

Wave::Wave(double a, double f, double c, Vector2 source, double phaseChange, std::vector<int> numbers) :
    _a(a),
    _f(f),
    _c(c),
	_phaseChange(phaseChange)
{
    _source = source;
	for (int i = 0; i < numbers.size(); i++)
		addWave(numbers[i]);
}

void Wave::setSource(Vector2 source)
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

double rectangular(double x)
{
	if (x < -0.5 || x > 0.5)
		return 0;
	return 1;
}

double Wave::getIntensity(Vector2 p, double t)
{
    Vector2 dist = p - _source;
    double r = dist.norm();
    double b = 6;
	double l = _c / _f;

	t -= _phaseChange;

	double rect;
	if (_waves.size() > 0)
	{
		rect = 0;
		for (int i = 0; i < _waves.size(); i++)
			rect += rectangular((r - _c * t + l / 2.0 + (double)_waves[i] * l) / _c * _f);
		if (rect == 0)
			return 0;
	}
	else
		rect = 1;

	return _a * cos(2 * M_PI*_f * (r / _c - t) + M_PI / 2.0) * exp(-r / l) * rect;
}

void Wave::addWave(int number)
{
	for (int i = 0; i < _waves.size(); i++)
		if (_waves[i] == number)
			return;
	_waves.push_back(number);
}
