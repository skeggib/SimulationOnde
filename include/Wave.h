#pragma once

#define M_PI		3.14159265358979323846
#define M_PI_2		1.57079632679489661923

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

#include "Vector2.h"
#include "Wall.h"

/*
Represente une vague generee par une impulsion
*/
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

	Wave* _causeWave;
	Wall* _causeWall;

public:

    /*
    a : Amplitude a la source a t = 0
    coefAttAmplitude : Coefficient d'attenuation de l'amplitude dans le temps
    f : Frequence
    c : Celerite
    source : Position de la source de la vague
    */
	Wave(double a = 1, double coefAttAmplitude = 0.3, double f = 1, double c = 1, Vector2 source = Vector2(), double phaseChange = 0);

	void setSource(Vector2 source);
	Vector2 getSource();

	// Mettre a true si la vague est une source, a false si elle est une reflexion
	void setIsSource(bool isSource);
	bool isSource();

	// Si la vague est une reflexion, causeWave est sa source
	void setCauseWave(Wave* wave);
	Wave* getCauseWave();

	// Si la vague est une reflexion, causeWall est le mur sur lequel la source se reflechie
	void setCauseWall(Wall* wall);
	Wall* getCauseWall();

	void setPhaseChange(double t);

	// Amplitude a la source en fonction du temps
	double getAmplitude(double t);

	// Intensite de la vague a un point du plan en fonction du temps
    double getIntensity(Vector2 p, double t);
};
