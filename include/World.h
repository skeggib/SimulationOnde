#pragma once

#include <vector>

#include "Form.h"
#include "Camera.h"

/*
Represente l'environnement 3D.
Contient tout les objets qui heritent de Form.
Permet de les afficher en fonction de la position de la camera
et de les mettre a jour en fonction du temps.
*/
class World
{
private:

    std::vector<Form*> _forms;

public:

    World();

    // Afficher l'environnement
    void render(Camera camera);

    // Mettre a jour l'environnement
    void update(double delta_t);

    // Ajouter un objet dans l'environnement
    void add(Form* form);
};
