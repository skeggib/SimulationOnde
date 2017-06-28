#include "Wall.h"

Wall::Wall(Vector2 p1, Vector2 p2, double z1, double z2) :
	_p1(p1),
	_p2(p2),
	_x1(p1.x),
	_x2(p2.x),
	_y1(p1.y),
	_y2(p2.y),
	_z1(z1),
	_z2(z2)
{
	_a = p2.y - p1.y;
	_b = p1.x - p2.x;
	_c = -(_a * p1.x + _b * p1.y);
}

void Wall::render()
{
	Vector2 v = _p2 - _p1;
	Vector2 vp;

	if (v.y == 0)
	{
		vp.y = 1;
		vp.x = (-vp.y * v.y) / v.x;
	}
	else
	{
		vp.x = 1;
		vp.y = (-vp.x * v.x) / v.y;
	}

	vp = vp * (1 / vp.norm()) * 0.05;

	Form::startRendering();

	glBegin(GL_POLYGON);
	{
		glColor3d(0.5, 0.5, 0.5);

		glVertex3d(_x1 - vp.x, _y1 - vp.y, _z1);
		glVertex3d(_x2 - vp.x, _y2 - vp.y, _z1);
		glVertex3d(_x2 - vp.x, _y2 - vp.y, _z2);
		glVertex3d(_x1 - vp.x, _y1 - vp.y, _z2);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor3d(0.5, 0.5, 0.5);

		glVertex3d(_x1 + vp.x, _y1 + vp.y, _z1);
		glVertex3d(_x2 + vp.x, _y2 + vp.y, _z1);
		glVertex3d(_x2 + vp.x, _y2 + vp.y, _z2);
		glVertex3d(_x1 + vp.x, _y1 + vp.y, _z2);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor3d(0.5, 0.5, 0.5);

		glVertex3d(_x1 + vp.x, _y1 + vp.y, _z2);
		glVertex3d(_x1 - vp.x, _y1 - vp.y, _z2);
		glVertex3d(_x2 - vp.x, _y2 - vp.y, _z2);
		glVertex3d(_x2 + vp.x, _y2 + vp.y, _z2);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor3d(0.5, 0.5, 0.5);

		glVertex3d(_x1 + vp.x, _y1 + vp.y, _z1);
		glVertex3d(_x1 - vp.x, _y1 - vp.y, _z1);
		glVertex3d(_x1 - vp.x, _y1 - vp.y, _z2);
		glVertex3d(_x1 + vp.x, _y1 + vp.y, _z2);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glColor3d(0.5, 0.5, 0.5);

		glVertex3d(_x2 + vp.x, _y2 + vp.y, _z1);
		glVertex3d(_x2 - vp.x, _y2 - vp.y, _z1);
		glVertex3d(_x2 - vp.x, _y2 - vp.y, _z2);
		glVertex3d(_x2 + vp.x, _y2 + vp.y, _z2);
	}
	glEnd();

	Form::endRendering();
}

void Wall::update(double delta_t)
{

}

Vector2 Wall::getSymmetry(Vector2 m)
{
	Vector2 mp;

	Vector2 v = _p2 - _p1;
	
	Vector2 vp;

	if (v.y == 0)
	{
		vp.y = 1;
		vp.x = (-vp.y * v.y) / v.x;
	}
	else
	{
		vp.x = 1;
		vp.y = (-vp.x * v.x) / v.y;
	}

	double ap = (m + vp).y - m.y;
	double bp = m.x - (m + vp).x;
	double cp = -(ap * m.x + bp * m.y);

	Vector2 i;

	i.x = (((_b * cp) / (_a * bp)) - (_c / _a)) / (1 - ((_b * ap) / (_a * bp)));
	i.y = -(ap * i.x + cp) / bp;

	return m + 2 * (i - m);
}

bool Wall::sameSide(Vector2 v1, Vector2 v2)
{
	double s1 = (v1.x - _p1.x) * (_p2.y - _p1.y) - (v1.y - _p1.y) * (_p2.x - _p1.x);
	double s2 = (v2.x - _p1.x) * (_p2.y - _p1.y) - (v2.y - _p1.y) * (_p2.x - _p1.x);

	if ((s1 < 0 && s2 < 0) || (s1 >= 0 && s2 >= 0))
		return true;
	return false;
}

double Wall::getA()
{
	return _a;
}

double Wall::getB()
{
	return _b;
}

double Wall::getC()
{
	return _c;
}