#pragma once

#include <windows.h>

#include <GL/gl.h>
#include <GL/GLU.h>

#include "Color.h"
#include "Animation.h"
#include "Point.h"

// Generic class to render and animate an object
class Form
{
    private:
        Color _color;
        Animation _animation;
    public:
        Animation& getAnimation();
        void setAnimation(Animation& animation);
        // This method should update the animation object with the corresponding physical model
        // It has to be done in each inherited class, otherwise all forms will have the same movements !
        // Virtual method for dynamic function call
        // Pure virtual to ensure all objects have their physics implemented
        virtual void update(double delta_t) = 0;
        // Virtual method : Form is a generic type, only setting color and reference position

        // Should be called at the beginning of render()
        virtual void startRendering();
        // Should be called at the end of render()
        virtual void endRendering();
        // Renders the form
        virtual void render() = 0;
};
