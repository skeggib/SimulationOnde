#pragma once

#include "Point.h"
#include "Vector.h"

class Camera
{
private:

    Point _position;
    double _theta = 0;
    double _phi = 0;

public:

    Camera(Point position);

    Point getPosition();
    double getTheta();
    double getPhi();
    void rotateH(double angle);
    void rotateV(double angle);
    void move(Vector vec);
};
