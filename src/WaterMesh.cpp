#include "WaterMesh.h"

WaterMesh::WaterMesh(Point origin, double size, int splits, Wave wave) :
    _size(size),
    _splits(splits),
    _squares(splits, std::vector<Square>(splits, Square())),
    _elapsedTime(0)
{
    getAnimation().setPos(origin);
    _wave = wave;

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

    _elapsedTime += delta_t;

    for (double x = 0; x < count(); x++)
    {
        for (double y = 0; y < count(); y++)
        {
            double x2 = x - count() / 2;
            double y2 = y - count() / 2;
            x2 *= _size / _splits;
            y2 *= _size / _splits;
            double intensity = _wave.getIntensity(Point2D(x2, y2), _elapsedTime);
            setIntensity(x, y, intensity);
        }
    }
}

unsigned int WaterMesh::count()
{
    return _splits + 1;
}

void WaterMesh::setIntensity(int x, int y, double intensity)
{
    if (x < 0 || y < 0 || x > _splits || y > _splits)
        return;

    if (x > 0 && y > 0)
        _squares[x-1][y-1].setIntensity4(intensity);
    if (x > 0 && y < _splits)
        _squares[x-1][y].setIntensity2(intensity);
    if (x < _splits && y > 0)
        _squares[x][y-1].setIntensity3(intensity);
    if (x < _splits && y < _splits)
        _squares[x][y].setIntensity1(intensity);
}
