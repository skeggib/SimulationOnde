#include "World.h"

#include <iostream>

World::World() { }

void World::render(Camera camera)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 0, 0, -1, 0, 0, 0, 0, 1);

	Vector3 cam_pos = camera.getPosition();
    glRotated(camera.getPhi(), 0, 1, 0);
    glRotated(camera.getTheta(), 0, 0, 1);
    glTranslated(-cam_pos.x, -cam_pos.y, -cam_pos.z);

    // Render the coordinates system
    glBegin(GL_LINES);
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(1, 0, 0);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(0, 1, 0);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(0, 0, 1);
    }
    glEnd();

    for (unsigned int i = 0; i < _forms.size(); i++)
        if (_forms[i])
            _forms[i]->render();
}

void World::update(double delta_t)
{
    for (unsigned int i = 0; i < _forms.size(); i++)
        if (_forms[i])
            _forms[i]->update(delta_t);
}

void World::add(Form* form)
{
    _forms.push_back(form);
}
