#pragma once

#include "Form.h"
#include "Triangle.h"
#include "Point.h"

class Square : public Form
{
private:

    Triangle _t1, _t2;
    double _i1, _i2, _i3, _i4;
    double _size;

public:

    Square(Point origin = Point(), double size = 1,
           double i1 = 0, double i2 = 0, double i3 = 0, double i4 = 0);

    void render();
    void update(double delta_t);

    void setIntensity1(double intensity);
    void setIntensity2(double intensity);
    void setIntensity3(double intensity);
    void setIntensity4(double intensity);
};
