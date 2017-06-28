#pragma once

#include "Form.h"
#include "Vector2.h"


class Wall : public Form
{

private:

	double _a, _b;

	double _x1, _x2;
	double _y1, _y2;
	double _z1, _z2;

public:

	Wall(Vector2 v1, Vector2 v2, double z1, double z2);

	double getA();
	double getB();

	void render();
	void update(double delta_t);

};

