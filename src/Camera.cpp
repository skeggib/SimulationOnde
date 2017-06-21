#include "Camera.h"

Camera::Camera(Point position)
{
    _position = position;
}

Point Camera::getPosition()
{
    return _position;
}
