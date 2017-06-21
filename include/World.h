#pragma once

#include <vector>

#include "Form.h"
#include "Camera.h"

class World
{
private:

    std::vector<Form*> _forms;

public:

    World();

    void render(Camera camera);
    void update(double delta_t);

    void add(Form* form);
};
