#include "Square.h"

Square::Square( Point origin, double size,
                double i1, double i2, double i3, double i4) :
_t1(Point(-size/2, -size/2, i1),
   Point(size/2, -size/2, i2),
   Point(-size/2, size/2, i3)),
_t2(Point(size/2, size/2, i4),
   Point(-size/2, size/2, i3),
   Point(size/2, -size/2, i2)),
_i1(i1),
_i2(i2),
_i3(i3),
_i4(i4),
_size(size)
{
    getAnimation().setPos(origin);
}

void Square::render()
{
    Form::startRendering();

    _t1.render();
    _t2.render();

    Form::endRendering();
}

void Square::update(double delta_t)
{
    _t1.update(delta_t);
    _t2.update(delta_t);
}

void Square::setIntensity1(double intensity)
{
    _i1 = intensity;
    _t1 = Triangle(Point(-_size/2, -_size/2, _i1),
                  Point(_size/2, -_size/2, _i2),
                  Point(-_size/2, _size/2, _i3));
}

void Square::setIntensity2(double intensity)
{
    _i2 = intensity;
    _t1 = Triangle(Point(-_size/2, -_size/2, _i1),
                  Point(_size/2, -_size/2, _i2),
                  Point(-_size/2, _size/2, _i3));
    _t2 = Triangle(Point(_size/2, _size/2, _i4),
                  Point(-_size/2, _size/2, _i3),
                  Point(_size/2, -_size/2, _i2));
}

void Square::setIntensity3(double intensity)
{
    _i3 = intensity;
    _t1 = Triangle(Point(-_size/2, -_size/2, _i1),
                  Point(_size/2, -_size/2, _i2),
                  Point(-_size/2, _size/2, _i3));
    _t2 = Triangle(Point(_size/2, _size/2, _i4),
                  Point(-_size/2, _size/2, _i3),
                  Point(_size/2, -_size/2, _i2));
}

void Square::setIntensity4(double intensity)
{
    _i4 = intensity;
    _t2 = Triangle(Point(_size/2, _size/2, _i4),
                  Point(-_size/2, _size/2, _i3),
                  Point(_size/2, -_size/2, _i2));
}
