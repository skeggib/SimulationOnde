#include "Form.h"

Animation& Form::getAnimation()
{
    return _animation;
}

void Form::setAnimation(Animation& animation)
{
    _animation = animation;
}

void Form::update(double delta_t)
{
    // Nothing to do here, animation update is done in child class method
}

void Form::startRendering()
{
    glPushMatrix();
    Vector3 org = _animation.getPos();
    glRotated(_animation.getPhi(), 0, 0, 1);
    glRotated(_animation.getTheta(), 1, 0, 0);
    glTranslated(org.x, org.y, org.z);
    glColor3f(_color.r, _color.g, _color.b);
}

void Form::endRendering()
{
    glPopMatrix();
}
