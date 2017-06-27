#include "Slider.h"

Slider::Slider(void)
{
    _destBar = SDL_Rect{0,0,0,0};
    _destCur = SDL_Rect{0,0,0,0};
    _min = 0;
    _max = 0;
    _default = 0;
    _pos = 0;
}

Slider::Slider(SDL_Rect destBar, SDL_Rect destCur)
{
    _destBar = destBar;
    _destCur = destCur;
    _min = 0;
    _max = 0;
    _default = 0;
    _pos = 0;
}

Slider::Slider(double minV, double maxV, double defaultV)
{
    _destBar = SDL_Rect{0,0,0,0};
    _destCur = SDL_Rect{0,0,0,0};
    _min = minV;
    _max = maxV;
    _default = defaultV;
    _pos = 0;
}

Slider::Slider(double minV, double maxV, double defaultV, SDL_Rect destBar, SDL_Rect destCur)
{
    _destBar = destBar;
    _destCur = destCur;
    _min = minV;
    _max = maxV;
    _default = defaultV;
    _pos = 0;
}

Slider::~Slider(void)
{

}

double Slider::getMin(void) const
{
    return _min;
}

void Slider::setMin(double minV)
{
    _min = minV;
}

double Slider::getMax(void) const
{
    return _max;
}

void Slider::setMax(double maxV)
{
    _max = maxV;
}

double Slider::getDefault(void) const
{
    return _default;
}

void Slider::setDefault(double defaultV)
{
    _default = defaultV;
}

double Slider::getPos(void) const
{
    return _pos;
}

void Slider::setPos(double pos)
{
    _pos = pos;
}

SDL_Rect Slider::getDestBar(void) const
{
    return _destBar;
}

void Slider::setDestBar(SDL_Rect dest)
{
    _destBar = dest;
}

SDL_Rect Slider::getDestCur(void) const
{
    return _destCur;
}

void Slider::setDestCur(SDL_Rect dest)
{
    _destCur = dest;
}

