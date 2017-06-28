#pragma once
#define M_PI		3.14159265358979323846
#define M_PI_2		1.57079632679489661923

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "Vector3.h"

class Camera
{
private:

	Vector3 _position;
    double _phi;
    double _theta;

public:

    Camera(Vector3 position = Vector3(0,0,0), double phi = 0, double theta = 0);

	Vector3 getPosition();
    double getPhi();
    double getTheta();

    void setPosition(Vector3 position);
    void setPhi(double phi);
    void setTheta(double theta);

    void rotateH(double angle);
    void rotateV(double angle);
    void move(int forward, int left, int up);
};
