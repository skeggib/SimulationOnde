#include "WaterMesh.h"

const double WaterMesh::MinColor = 0.5;
const double WaterMesh::MaxColor = 0.9;

WaterMesh::WaterMesh(Vector3 origin, double size, int splits) :
    _size(size),
    _elapsedTime(0)
{
    getAnimation().setPos(origin);
	setSplits(splits);
}

void WaterMesh::render()
{
	double squareSize = _size / (double)_splits;
	double x1, y1, x2, y2;
	double i1, i2, i3, i4;

	Vector3 sun(-1, 1, -1);
	double sun_norm = sun.norm();

	Vector3 scalar;
	double angle, color;

	Vector3 v1, v2;

    Form::startRendering();

	glBegin(GL_TRIANGLES);

	for (unsigned int i = 0; i < _intensities.size() - 1; i++)
	{
		for (unsigned int j = 0; j < _intensities[i].size() - 1; j++)
		{
			i1 = _intensities[i][j];
			i2 = _intensities[i + 1][j];
			i3 = _intensities[i][j + 1];
			i4 = _intensities[i + 1][j + 1];

			x1 = squareSize * (double)i - _size / 2.0;
			y1 = squareSize * (double)j - _size / 2.0;

			x2 = squareSize * ((double)i + 1) - _size / 2.0;
			y2 = squareSize * ((double)j + 1) - _size / 2.0;

			v1.x = x2 - x1;
			v1.y = 0;
			v1.z = i2 - i1;

			v2.x = 0;
			v2.y = y2 - y1;
			v2.z = i3 - i1;

			scalar = v1 ^ v2;
			angle = - (scalar * sun) / (scalar.norm() * sun_norm);
			color = angle * (MaxColor - MinColor) + MinColor;

			glColor3f(0, 0.1, color);
			glVertex3d(x1, y1, i1);
			glVertex3d(x1, y2, i3);
			glVertex3d(x2, y1, i2);

			glColor3f(0, 0.1, color);
			glVertex3d(x1, y2, i3);
			glVertex3d(x2, y1, i2);
			glVertex3d(x2, y2, i4);
		}
	}

	glEnd();

    Form::endRendering();
}

void WaterMesh::update(double delta_t)
{
    _elapsedTime += delta_t;

	std::vector<Wave*>::iterator it = _waves.begin();
	while (it != _waves.end())
	{
		if ((*it)->getAmplitude(_elapsedTime) < 1e-4)
			it = _waves.erase(it);
		if (it != _waves.end())
			it++;
	}

	double count = _intensities.size();
    for (int x = 0; x < count; x++)
    {
        for (int y = 0; y < count; y++)
        {
            double x2 = (double)x - count / 2.0;
            double y2 = (double)y - count / 2.0;
            x2 *= _size / _splits;
            y2 *= _size / _splits;

            double intensity = 0;
			for (int i = 0; i < _waves.size(); i++)
				if (_waves[i] != NULL)
					intensity += _waves[i]->getIntensity(Vector2(x2, y2), _elapsedTime);
            
			setIntensity(x, y, intensity);
        }
    }
}

void WaterMesh::addWave(Wave * wave)
{
	for (int i = 0; i < _waves.size(); i++)
		if (_waves[i] == wave)
			return;
	wave->setPhaseChange(_elapsedTime);
	_waves.push_back(wave);
}

void WaterMesh::setIntensity(int x, int y, double intensity)
{
    if (x < 0 || y < 0 || x > _splits || y > _splits)
        return;

	_intensities[x][y] = intensity;
}

void WaterMesh::setSplits(int splits)
{
	_intensities = std::vector< std::vector<double> >(splits + 1, std::vector<double>(splits + 1, 0));
	_splits = splits;
}

int WaterMesh::getSplits()
{
	return _splits;
}
