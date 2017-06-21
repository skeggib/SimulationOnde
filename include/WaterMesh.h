#pragma once

#include <vector>

#include "Form.h"
#include "Square.h"

class WaterMesh : public Form
{
private:

    std::vector< std::vector<Square> > _squares;
    int _splits;

public:

    WaterMesh(Point origin, double size, int splits);

    void render();
    void update(double delta_t);

    /**
     * @brief Counts the number of points in one direction (axis)
     * @return The number of points in one direction (axis)
     */
    unsigned int count();

    void setIntensity(int x, int y, double intensity);
};
