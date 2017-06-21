#include "Animation.h"

Animation::Animation(double ph, double th,
                  Vector accel, Vector speed, Point p)
{
    phi = ph;
    theta = th;
    acc = accel;
    spd = speed;
    pos = p;
}
