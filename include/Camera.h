#pragma once

#include "Point.h"
#include "Vector.h"

class Camera
{
private:

    Point _position;
    double _phi;
    double _theta;

public:

    Camera(Point position = Point(0,0,0), double phi = 0, double theta = 0);

    Point getPosition();
    double getPhi();
    double getTheta();

    void rotateH(double angle);
    void rotateV(double angle);
    void move(Vector vec);
};
