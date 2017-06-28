#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <SDL2/SDL.h>
#include <string>

#include "ttf.h"

#define CLICK_COLOR     100
#define UNCLICK_COLOR   255

class Button
{
public:
    Button(void);
    Button(std::string text, SDL_Rect dest);

    std::string getText(void) const;
    void setText(std::string text);
    SDL_Rect getDest(void) const;
    void setDest(SDL_Rect dest);

    void draw(SDL_Renderer *renderer, TTF_Font *font, SDL_Event e);

    bool isClick(SDL_Event e);

private:
    std::string _text;
    SDL_Rect _dest;
};

#endif // BUTTON_H_INCLUDED
