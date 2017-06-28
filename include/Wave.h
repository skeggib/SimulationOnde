#pragma once

#define M_PI		3.14159265358979323846
#define M_PI_2		1.57079632679489661923

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

#include "Vector2.h"

class Wave
{

private:

    double _a;
	double _coefAttAmplitude;
    double _f;
    double _c;

	double _phaseChange;

    Vector2 _source;
	bool _isSource;

public:

	Wave(double a = 1, double coefAttAmplitude = 0.3, double f = 1, double c = 1, Vector2 source = Vector2(), double phaseChange = 0);

	void setSource(Vector2 source);
	Vector2 getSource();

	void setIsSource(bool isSource);
	bool isSource();

	void setPhaseChange(double t);

	double getAmplitude(double t);
    double getIntensity(Vector2 p, double t);
};
