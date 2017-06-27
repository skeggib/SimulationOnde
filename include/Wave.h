#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

#include "Vector2.h"
#include "Cosinus.h"

class Wave
{

private:

    double _a;
	double _coefAttAmplitude;
    double _f;
    double _c;

	double _phaseChange;

    Vector2 _source;

	static const Cosinus cosinus;

	double getAmplitude(double t);

public:

	Wave(double a = 1, double coefAttAmplitude = 0.3, double f = 1, double c = 1, Vector2 source = Vector2(), double phaseChange = 0);

	void setSource(Vector2 source);

    double getIntensity(Vector2 p, double t);
};
