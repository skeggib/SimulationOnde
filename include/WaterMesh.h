#pragma once

#include <vector>

#include "Form.h"
#include "Wave.h"
#include "Wall.h"

/*
Discretisation d'un plan permettant d'afficher la vague.
Contient un tableau a deux dimensions representant les intensites
aux points de discretisation.
*/
class WaterMesh : public Form
{
private:

    std::vector< std::vector<double> > _intensities;
    double _size;
    int _splits;
    double _elapsedTime;

	std::vector<Wall*> _walls;
	std::vector<Wave*> _waves;

	// Changer l'intensite a un point du plan
    void setIntensity(int x, int y, double intensity);

public:

	static const double MinColor;
	static const double MaxColor;

	/*
	Vector3 origin : position du plan
	double size : taille du plan
	int splits : nombre de divisions sur l'axe X et Y
	*/
    WaterMesh(Vector3 origin, double size, int splits);

    void render();
    void update(double delta_t);

    // Ajouter un mur
	void addWall(Wall* wall);

	// Ajouter une vague, elle sera supprimee lorsqu'elle deviendra plate
	void addWave(Wave* wave);

	// Changer le nombre de divisions
	void setSplits(int splits);
	int getSplits();

	// Compter le nombre de vagues
	int countWaves();
};
