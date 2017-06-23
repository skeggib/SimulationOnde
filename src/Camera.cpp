#include "Camera.h"

Camera::Camera(Point position, double phi, double theta)
{
    _position = position;
    _phi = phi;
    _theta = theta;
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
    _theta += angle;
    if (_theta < 0)
    {
        double delta = -_theta;
        _theta = 360 - delta;
    }
    else if (_theta > 360)
    {
        double delta = _theta - 360;
        _theta = 0 + delta;
    }
}

void Camera::rotateV(double angle)
{
    _phi += angle;
    if (_phi < -89)
    {
        _phi = -89;
    }
    else if (_phi > 89)
    {
        _phi = 89;
    }
}
