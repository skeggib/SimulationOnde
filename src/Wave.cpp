#include "Wave.h"

const Cosinus Wave::cosinus = Cosinus(100);

double Wave::getAmplitude(double t)
{
	if (t < 0)
		return 0;
	return _a * exp(-t / _coefAttAmplitude);
}

Wave::Wave(double a, double coefAttAmplitude, double f, double c, Vector2 source, double phaseChange) :
	_a(a),
	_coefAttAmplitude(coefAttAmplitude),
    _f(f),
    _c(c),
	_source(source),
	_phaseChange(phaseChange)
{

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
    double x = dist.norm();
	double l = _c / _f;

	t -= _phaseChange;

	return getAmplitude(t - x/_c) * cos(2 * M_PI*_f * (x / _c - t) - M_PI / 2.0) * exp(-x / l);
}
