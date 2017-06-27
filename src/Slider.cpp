#include "Slider.h"

Slider::Slider(void)
{
    _destBar = SDL_Rect{0,0,0,0};
    _destCur = SDL_Rect{0,0,0,0};
    _min = 0;
    _max = 0;
    _default = 0;
    resetPos();
}

Slider::Slider(SDL_Rect destBar, SDL_Rect destCur)
{
    _destBar = destBar;
    _destCur = destCur;
    _destCur.x = _destBar.x;
    _destCur.y = _destBar.y + _destBar.h / 2 - _destCur.h / 2;
    _min = 0;
    _max = 0;
    _default = 0;
    resetPos();
}

Slider::Slider(double minV, double maxV, double defaultV)
{
    _destBar = SDL_Rect{0,0,0,0};
    _destCur = SDL_Rect{0,0,0,0};
    _min = minV;
    _max = maxV;
    _default = defaultV;
    resetPos();
}

Slider::Slider(double minV, double maxV, double defaultV, SDL_Rect destBar, SDL_Rect destCur)
{
    _destBar = destBar;
    _destCur = destCur;
    _destCur.x = _destBar.x;
    _destCur.y = _destBar.y + _destBar.h / 2 - _destCur.h / 2;
    _min = minV;
    _max = maxV;
    _default = defaultV;
    resetPos();
}

Slider::~Slider(void)
{

}

void Slider::move(int x, int y)
{
    if(y > _destCur.y && y < _destCur.y + _destCur.h)
    {
        if(x > _destBar.x + _destBar.w - _destCur.w / 2)
        {
            _destCur.x = _destBar.x + _destBar.w - _destCur.w / 2;
        }
        else if(x < _destBar.x)
        {
            _destCur.x = _destBar.x - _destCur.w / 2;
        }
        else
        {
            _destCur.x = x - _destCur.w / 2;
        }
    }
}
void Slider::resetPos(void)
{
    setValue(_default);
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

double Slider::getValue(void)
{
    double pos;
    pos = (((double)(_destCur.x + _destCur.w/2 - _destBar.x)/(double)(_destBar.w)));
    pos *= (double)(_max - _min);
    pos += _min;
    return pos;
}

void Slider::setValue(double pos)
{
    _destCur.x = (pos - _min)/(_max - _min) * _destBar.w;

    _destCur.x += _destBar.x;
//    std::cout << "> CUR : " << _destCur.x << " = " << getPos() << std::endl;
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

void Slider::draw(SDL_Renderer *renderer) const
{
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderFillRect(renderer, &_destBar);

    SDL_SetRenderDrawColor(renderer, 100,100,100,255);
    SDL_RenderFillRect(renderer, &_destCur);
}
