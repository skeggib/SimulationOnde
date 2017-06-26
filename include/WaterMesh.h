#pragma once

#include <vector>

#include "Form.h"
#include "Wave.h"

class WaterMesh : public Form
{
private:

    std::vector< std::vector<double> > _intensities;
    double _size;
    int _splits;
    double _elapsedTime;

	std::vector<Wave*> _waves;

    void setIntensity(int x, int y, double intensity);

public:

	static const double MinColor;
	static const double MaxColor;

    WaterMesh(Vector3 origin, double size, int splits);

    void render();
    void update(double delta_t);

	void addWave(Wave* wave);

	void setSplits(int splits);
	int getSplits();
};
