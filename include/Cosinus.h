#pragma once

#define M_PI		3.14159265358979323846

#include <cmath>
#include <vector>

class Cosinus
{

private :
    
	std::vector<double> _values;

public :
    
    Cosinus(int taille_tab);
    double cos(double value) const;

};