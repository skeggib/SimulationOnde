#include "Square.h"

Square::Square(Vector3 origin, double size, double i1, double i2, double i3, double i4) :
	_i1(i1),
	_i2(i2),
	_i3(i3),
	_i4(i4),
	_size(size),
	_t1(Vector3(-size / 2.0, -size / 2.0, i1),
		Vector3(size, 0, i2 - i1),
		Vector3(0, size, i3 - i1)),
	_t2(Vector3(size / 2.0, size / 2.0, i4),
		Vector3(-size, 0, i3 - i4),
		Vector3(0, -size, i2 - i4))
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
	_t1 = Triangle(
		Vector3(-_size / 2, -_size / 2, _i1),
		Vector3(_size, 0, _i2 - _i1),
		Vector3(0, _size, _i3 - _i1));
}

void Square::setIntensity2(double intensity)
{
    _i2 = intensity;
	_t1 = Triangle(
		Vector3(-_size / 2, -_size / 2, _i1),
		Vector3(_size, 0, _i2 - _i1),
		Vector3(0, _size, _i3 - _i1));
    _t2 = Triangle(
		Vector3(_size / 2, _size / 2, _i4),
		Vector3(-_size, 0, _i3 - _i4),
		Vector3(0, -_size, _i2 - _i4));
}

void Square::setIntensity3(double intensity)
{
    _i3 = intensity;
	_t1 = Triangle(
		Vector3(-_size / 2, -_size / 2, _i1),
		Vector3(_size, 0, _i2 - _i1),
		Vector3(0, _size, _i3 - _i1));
	_t2 = Triangle(
		Vector3(_size / 2, _size / 2, _i4),
		Vector3(-_size, 0, _i3 - _i4),
		Vector3(0, -_size, _i2 - _i4));
}

void Square::setIntensity4(double intensity)
{
    _i4 = intensity;
	_t2 = Triangle(
		Vector3(_size / 2, _size / 2, _i4),
		Vector3(-_size, 0, _i3 - _i4),
		Vector3(0, -_size, _i2 - _i4));
}
