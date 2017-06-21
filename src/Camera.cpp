#include "Camera.h"

Camera::Camera(Point position)
{
    _position = position;
}

Point Camera::getPosition()
{
    return _position;
}

double Camera::getPhi()
{
    return _phi;
}

double Camera::getTheta()
{
    return _theta;
}

void Camera::rotateH(double angle)
{
    _phi += angle;
    if (_phi < 0)
    {
        double delta = -_phi;
        _phi = 360 - delta;
    }
    else if (_phi >= 360)
    {
        double delta = 360 - _phi;
        _phi = 0 + delta;
    }
}

void Camera::rotateV(double angle)
{
    _theta += angle;
    if (_theta < 0)
    {
        double delta = -_theta;
        _theta = 360 - delta;
    }
    else if (_theta >= 360)
    {
        double delta = 360 - _theta;
        _theta = 0 + delta;
    }
}
