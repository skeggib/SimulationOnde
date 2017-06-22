#pragma once

#include <vector>

#include "Form.h"
#include "Square.h"
#include "Wave.h"

class WaterMesh : public Form
{
private:

    std::vector< std::vector<Square> > _squares;
    double _size;
    int _splits;
    Wave _wave;
    double _elapsedTime;

    void setIntensity(int x, int y, double intensity);

public:

    WaterMesh(Point origin, double size, int splits, Wave wave);

    void render();
    void update(double delta_t);

    /**
     * @brief Counts the number of points in one direction (axis)
     * @return The number of points in one direction (axis)
     */
    unsigned int count();
};
