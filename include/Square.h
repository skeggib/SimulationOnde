#pragma once

#include "Form.h"
#include "Triangle.h"
#include "Point.h"

class Square : public Form
{
private:

    Triangle t1, t2;

public:

    Square(Point origin = Point(), double size = 1,
           double i1 = 0, double i2 = 0, double i3 = 0, double i4 = 0);

    void render();
    void update(double delta_t);
};
