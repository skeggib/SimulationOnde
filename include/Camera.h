#pragma once

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

    void rotateH(double angle);
    void rotateV(double angle);
    void move(Vector3 vec);
};
