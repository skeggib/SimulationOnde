#include "Slider.h"

Slider::Slider(void)
{
    _x = 0;
    _y = 0;
    _name = "Slider";
    _destBar = SDL_Rect{0,0,0,0};
    _destCur = SDL_Rect{0,0,0,0};
    _min = 0;
    _max = 0;
    _default = 0;
    resetPos();
}

Slider::Slider(std::string name, double minV, double maxV, double defaultV, int x, int y)
{
    _x = x;
    _y = y;
    _name = name;
    _destBar = SDL_Rect{x, y + TEXT_HEIGHT, BAR_WIDTH, BAR_HEIGHT};
    _destCur = SDL_Rect{_destBar.x, _destBar.y + _destBar.h / 2 - CUR_HEIGHT / 2, CUR_WIDTH, CUR_HEIGHT};
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
    _destCur.x = (int)((pos - _min)/(_max - _min) * _destBar.w);

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

void Slider::draw(SDL_Renderer *renderer, TTF_Font *font, SDL_Color col)
{
    write(_name + " : " + doubleToString(getValue()), font, col, renderer, SDL_Rect{_destBar.x, _destBar.y - static_cast<int>(TEXT_HEIGHT*2.5), _destBar.w, TEXT_HEIGHT});

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderFillRect(renderer, &_destBar);

    SDL_SetRenderDrawColor(renderer, 100,100,100,255);
    SDL_RenderFillRect(renderer, &_destCur);
}
