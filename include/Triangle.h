#pragma once

#include <cmath>

#include "Form.h"
#include "Vector3.h"

class Triangle
{

private:

	Vector3 _origin;
    Vector3 _v1;
    Vector3 _v2;

public:

    static const double MinColor;
    static const double MaxColor;

    Triangle(Vector3 origin, Vector3 v1, Vector3 v2);

    void render();
    void update(double delta_t);
};
