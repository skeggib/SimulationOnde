#pragma once

#include "Point.h"
#include "Vector.h"

class Camera
{
private:

    Point _position;
    double _phi = 0;
    double _theta = 0;

public:

    Camera(Point position = Point(5,5,5), double phi = 315, double theta = 35);

    Point getPosition();
    double getPhi();
    double getTheta();

    void rotateH(double angle);
    void rotateV(double angle);
    void move(Vector vec);
};
