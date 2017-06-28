#include "Triangle.h"

const double Triangle::MinColor = 0.5;
const double Triangle::MaxColor = 0.9;

Triangle::Triangle(Vector3 origin, Vector3 v1, Vector3 v2) :
	_origin(origin),
	_v1(v1),
	_v2(v2)
{

}

#include <gl/GL.h>

void Triangle::render()
{
	Vector3 scalar = _v1 ^ _v2;
	Vector3 sun(-1, 1, -1);
	double dot = scalar * sun;
	double scalar_norm = scalar.norm();
	double sun_norm = sun.norm();
	double angle = -dot / (scalar_norm * sun_norm);
	double color = angle * (MaxColor - MinColor) + MinColor;

    //glBegin(GL_TRIANGLES);
    //{
        glColor3d(0,0.1,color);
        glVertex3d(_origin.x, _origin.y, _origin.z);
        glVertex3d(_origin.x + _v1.x, _origin.y + _v1.y, _origin.z + _v1.z);
        glVertex3d(_origin.x + _v2.x, _origin.y + _v2.y, _origin.z + _v2.z);
    //}
    //glEnd();
}

void Triangle::update(double delta_t)
{
    // Do nothing
}
