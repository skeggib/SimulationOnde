#include "Animation.h"

Animation::Animation(double ph, double th,
					 Vector3 accel, Vector3 speed, Vector3 p)
{
    phi = ph;
    theta = th;
    acc = accel;
    spd = speed;
    pos = p;
}
