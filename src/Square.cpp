#include "Square.h"

Square::Square( Point origin, double size,
                double i1, double i2, double i3, double i4) :
t1(Point(-size/2, -size/2, i1),
   Point(size/2, -size/2, i2),
   Point(-size/2, size/2, i3)),
t2(Point(size/2, size/2, i4),
   Point(-size/2, size/2, i3),
   Point(size/2, -size/2, i2))
{
    getAnimation().setPos(origin);
}

void Square::render()
{
    Form::startRendering();

    t1.render();
    t2.render();

    Form::endRendering();
}

void Square::update(double delta_t)
{
    t1.update(delta_t);
    t2.update(delta_t);
}
