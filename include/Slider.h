#ifndef SLIDER_H_INCLUDED
#define SLIDER_H_INCLUDED

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

#include "ttf.h"

#define CUR_WIDTH   20
#define CUR_HEIGHT  40
#define BAR_WIDTH   300
#define BAR_HEIGHT  4
#define TEXT_HEIGHT 26

class Slider
{
public:
    Slider(void);
    Slider(std::string name, double minV, double maxV, double defaultV, int x, int y);
    ~Slider(void);

    void move(int x, int y);
    void resetPos(void);

    double getMin(void) const;
    void setMin(double minV);
    double getMax(void) const;
    void setMax(double maxV);
    double getDefault(void) const;
    void setDefault(double defaultV);
    double getValue(void);
    void setValue(double pos);
    SDL_Rect getDestBar(void) const;
    void setDestBar(SDL_Rect dest);
    SDL_Rect getDestCur(void) const;
    void setDestCur(SDL_Rect dest);

    void draw(SDL_Renderer *renderer, TTF_Font *font, SDL_Color col);

private:
    int _x;
    int _y;
    std::string _name;
    double _min;
    double _max;
    double _default;

    SDL_Rect _destBar;
    SDL_Rect _destCur;
};


#endif // SLIDER_H_INCLUDED
