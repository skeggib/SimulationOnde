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
    double _elapsedTime;

	std::vector<Wave*> _waves;

    void setIntensity(int x, int y, double intensity);

public:

    WaterMesh(Vector3 origin, double size, int splits);

    void render();
    void update(double delta_t);

	void addWave(Wave* wave);

    /**
     * @brief Counts the number of points in one direction (axis)
     * @return The number of points in one direction (axis)
     */
    unsigned int count();
};
