#pragma once

#include "Form.h"
#include "Vector2.h"

// Mur definit par une equation de la forme ax+by+c=0
class Wall : public Form
{

private:

	Vector2 _p1, _p2;

	double _a, _b, _c;

	double _x1, _x2;
	double _y1, _y2;
	double _z1, _z2;

public:

	/// <summary>Construit un mur a partir de deux points</summary>
	/// <param name="p1">Point sur la droite</param>
	/// <param name="p2">Point sur la droite</param>
	/// <param name="z1">Limite basse du mur</param>
	/// <param name="z1">Limite haute du mur</param>
	Wall(Vector2 p1, Vector2 p2, double z1, double z2);

	void render();
	void update(double delta_t);

	Vector2 getSymmetry(Vector2 m);
	bool sameSide(Vector2 v1, Vector2 v2);

	/// <summary>Lire la valeur de a dans l'equation ax+by+c=0</summary>
	double getA();

	/// <summary>Lire la valeur de b dans l'equation ax+by+c=0</summary>
	double getB();

	/// <summary>Lire la valeur de c dans l'equation ax+by+c=0</summary>
	double getC();

};

