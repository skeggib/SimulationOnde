#ifndef TTF_H_INCLUDED
#define TTF_H_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

TTF_Font *loadFont(std::string const &font_path, int font_size);
SDL_Texture *createTextureFromString(std::string const &text, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer);
void write(std::string const &text, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer, SDL_Rect dest);
std::string intToString(int i);
std::string doubleToString(double d);
#endif // TTF_H_INCLUDED
