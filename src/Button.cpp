#include "Button.h"

Button::Button(void)
{
    _text = "Button";
    _dest = SDL_Rect{0,0,0,0};
}

Button::Button(std::string text, SDL_Rect dest)
{
    _text = text;
    _dest = dest;
}

std::string Button::getText(void) const
{
    return _text;
}

void Button::setText(std::string text)
{
    _text = text;
}

SDL_Rect Button::getDest(void) const
{
    return _dest;
}

void Button::setDest(SDL_Rect dest)
{
    _dest = dest;
}

void Button::draw(SDL_Renderer *renderer, TTF_Font *font, SDL_Event e)
{
    if(isClick(e)) // DRAW CLICKED
    {
        SDL_SetRenderDrawColor(renderer, UNCLICK_COLOR,UNCLICK_COLOR,UNCLICK_COLOR,255);
        SDL_RenderFillRect(renderer, &_dest);

        write(_text, font, SDL_Color{CLICK_COLOR,CLICK_COLOR,CLICK_COLOR,255}, renderer, _dest);
    }
    else // DRAW UNCLICKED
    {
        SDL_SetRenderDrawColor(renderer, CLICK_COLOR,CLICK_COLOR,CLICK_COLOR,255);
        SDL_RenderFillRect(renderer, &_dest);
        write(_text, font, SDL_Color{UNCLICK_COLOR,UNCLICK_COLOR,UNCLICK_COLOR,255}, renderer, _dest);
    }
}

bool Button::isClick(SDL_Event e)
{
    int cur_x, cur_y;
    SDL_GetMouseState(&cur_x, &cur_y);
    if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        if(
           cur_x > _dest.x + _dest.w ||
           cur_x < _dest.x ||
           cur_y > _dest.y + _dest.h ||
           cur_y < _dest.y
           )
            return false;
        else
        {
            return true;
        }
    }
    return false;
}
