#pragma once

#include "Vector3.h"

class Animation
{
    private:

        double phi, theta; // Azimuthal and polar angles for local coordinate system orientation
        Vector3 acc, spd; //  Instantaneous acceleration and speed
        Vector3 pos; // Instantaneous position of the local coordinate system origin

    public:

        Animation(double ph = 0.0, double th = 0.0,
                  Vector3 accel = Vector3(0.0, 0.0, 0.0),
                  Vector3 speed = Vector3(0.0, 0.0, 0.0),
				  Vector3 p = Vector3(0.0, 0.0, 0.0));

        const double getPhi() {return phi;}
        const double getTheta() {return theta;}
        void setPhi(double agl) {phi = agl;}
        void setTheta(double agl) {theta = agl;}
        const Vector3 getAccel() {return acc;}
        const Vector3 getSpeed() {return spd;}
        void setAccel(Vector3 vect) {acc = vect;}
        void setSpeed(Vector3 vect) {spd = vect;}
        const Vector3 getPos() {return pos;}
        void setPos(Vector3 pt) {pos = pt;}
};
