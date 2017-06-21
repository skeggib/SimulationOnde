#include "WaterMesh.h"

WaterMesh::WaterMesh(Point origin, double size, int splits) :
_squares(splits, std::vector<Square>(splits, Square()))
{
    getAnimation().setPos(origin);

    for (unsigned int i = 0; i < _squares.size(); i++)
        for (unsigned int j = 0; j < _squares[i].size(); j++)
            _squares[i][j] = Square(Point(
                                          size/(double)splits * (double)i - size/2.0 + size/(double)splits/2.0,
                                          size/(double)splits * (double)j - size/2.0 + size/(double)splits/2.0,
                                          0),
                                    size/(double)splits);
}

void WaterMesh::render()
{
    Form::startRendering();

    for (unsigned int i = 0; i < _squares.size(); i++)
        for (unsigned int j = 0; j < _squares[i].size(); j++)
                _squares[i][j].render();

    Form::endRendering();
}

void WaterMesh::update(double delta_t)
{
    for (unsigned int i = 0; i < _squares.size(); i++)
        for (unsigned int j = 0; j < _squares[i].size(); j++)
                _squares[i][j].update(delta_t);
}
