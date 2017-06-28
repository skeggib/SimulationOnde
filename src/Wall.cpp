#include "Wall.h"

Wall::Wall(Vector2 v1, Vector2 v2, double z1, double z2) :
	_x1(v1.x),
	_x2(v2.x),
	_y1(v1.y),
	_y2(v2.y),
	_z1(z1),
	_z2(z2)
{
	_a = (v2.y - v1.x) / (v2.x - v1.x);
	_b = v1.y - _a * v1.x;
}

double Wall::getA()
{
	return _a;
}

double Wall::getB()
{
	return _b;
}

void Wall::render()
{
	Form::startRendering();

	glBegin(GL_POLYGON);
	{
		glColor3d(0.5, 0.5, 0.5);

		glVertex3d(_x1, _y1, _z1);
		glVertex3d(_x2, _y2, _z1);
		glVertex3d(_x2, _y2, _z2);
		glVertex3d(_x1, _y1, _z2);
	}
	glEnd();

	Form::endRendering();
}

void Wall::update(double delta_t)
{

}
