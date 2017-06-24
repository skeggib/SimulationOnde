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

void Camera::setPosition(Point position)
{
    _position = position;
}

void Camera::setPhi(double phi)
{
    _phi = phi;
    if (_phi < -89)
    {
        _phi = -89;
    }
    else if (_phi > 89)
    {
        _phi = 89;
    }
}

void Camera::setTheta(double theta)
{
    _theta = theta;
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

void Camera::rotateH(double angle)
{
    setTheta(_theta + angle);
}

void Camera::rotateV(double angle)
{
    setPhi(_phi + angle);
}

void Camera::move(double forward, double left, double up)
{
    Vector Forward(sin(_theta*M_PI/180.0 + M_PI_2), cos(_theta*M_PI/180.0 + M_PI_2), 0);
    Vector Left(sin(_theta*M_PI/180.0), cos(_theta*M_PI/180.0), 0);
    Vector Up(0, 0, 1);

    _position = _position + (forward * Forward) + (left * Left) + (up * Up);
}
