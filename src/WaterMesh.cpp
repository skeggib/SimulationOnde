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

			// Calcul de la couleur en fonction de l'orientation du triangle
			scalar = v1 ^ v2;
			angle = - (scalar * sun) / (scalar.norm() * sun_norm);
			color = angle * (MaxColor - MinColor) + MinColor;

			glColor3d(0, 0.1, color);

			glVertex3d(x1, y1, i1);
			glVertex3d(x1, y2, i3);
			glVertex3d(x2, y1, i2);

			glVertex3d(x1, y2, i3);
			glVertex3d(x2, y1, i2);
			glVertex3d(x2, y2, i4);
		}
	}

	glEnd();

	for (unsigned int i = 0; i < _walls.size(); i++)
		if (_walls[i] != NULL)
			_walls[i]->render();

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

	// Pour chaque point de discretisation (x,y)
    for (int x = 0; x < count; x++)
    {
        for (int y = 0; y < count; y++)
        {
            double x2 = (double)x - count / 2.0;
            double y2 = (double)y - count / 2.0;
            x2 *= _size / _splits;
            y2 *= _size / _splits;

            // Calcul de l'intensite (somme de toutes les vagues)
            double intensity = 0;
			for (unsigned int i = 0; i < _waves.size(); i++)
			{
				if (_waves[i] != NULL)
				{
					bool compute = false;
					bool isSource = _waves[i]->isSource();

					Vector2 source;

					if (isSource)
					{
						source = _waves[i]->getSource();
					}
					else
					{
						source = _waves[i]->getCauseWave()->getSource();
					}

					// Prise en compte des murs pour que les vagues ne les traversent pas
					compute = true;
					for (unsigned int j = 0; j < _walls.size(); j++)
						if (!_walls[j]->sameSide(Vector2(x2, y2), source))
							compute = false;

					if (compute)
						intensity += _waves[i]->getIntensity(Vector2(x2, y2), _elapsedTime);
				}
			}

			setIntensity(x, y, intensity);
        }
    }
}

void WaterMesh::addWall(Wall * wall)
{
	for (unsigned int i = 0; i < _walls.size(); i++)
		if (_walls[i] == wall)
			return;
	_walls.push_back(wall);
}

void WaterMesh::addWave(Wave * wave)
{
    // Verifier que la vague n'existe pas dans le tableau
	for (unsigned int i = 0; i < _waves.size(); i++)
		if (_waves[i] == wave)
			return;

    // La vague doit demarrer au moment de l'ajout
	wave->setPhaseChange(_elapsedTime);
	_waves.push_back(wave);

	// Ajout des vagues representant les reflexions pour chaque mur
	for (unsigned int i = 0; i < _walls.size(); i++)
	{
		Vector2 symmetry = _walls[i]->getSymmetry(wave->getSource());
		Wave* reflection = new Wave(*wave);
		reflection->setSource(symmetry);
		reflection->setIsSource(false);
		reflection->setCauseWave(wave);
		reflection->setCauseWall(_walls[i]);
		_waves.push_back(reflection);
	}
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

int WaterMesh::countWaves()
{
	return _waves.size();
}
