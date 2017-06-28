#ifndef SLIDER_H_INCLUDED
#define SLIDER_H_INCLUDED

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

class Slider
{
public:
    Slider(void);
    Slider(SDL_Rect destBar, SDL_Rect destCur);
    Slider(double minV, double maxV, double defaultV);
    Slider(double minV, double maxV, double defaultV, SDL_Rect destBar, SDL_Rect destCur);
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

    void draw(SDL_Renderer *renderer) const;

private:
    double _min;
    double _max;
    double _default;

    SDL_Rect _destBar;
    SDL_Rect _destCur;
};


#endif // SLIDER_H_INCLUDED
