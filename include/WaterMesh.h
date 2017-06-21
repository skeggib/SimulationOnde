#pragma once

#include <vector>

#include "Form.h"
#include "Square.h"

class WaterMesh : public Form
{
private:

    std::vector< std::vector<Square> > _squares;

public:

    WaterMesh(Point origin, double size, int splits);

    void render();
    void update(double delta_t);
};
