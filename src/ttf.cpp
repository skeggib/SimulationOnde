#include "ttf.h"

TTF_Font *loadFont(std::string const &font_path, int font_size)
{
    TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);
    if(font == NULL)
    {
        std::cerr << "ERROR Loading font : " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    return font;
}

SDL_Texture *createTextureFromString(std::string const &text, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer)
{
    if(!font)
    {
        std::cerr << "ERROR Font was not initialized " << std::endl;
        exit(EXIT_FAILURE);
    }
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;

    surface = TTF_RenderText_Blended(font, text.c_str(), color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    return texture;
}

void write(std::string const &text, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer, SDL_Rect dest)
{
    SDL_Texture *texture = createTextureFromString(text, font, color, renderer);
    if(!texture)
    {
        std::cerr << "ERROR Loading texture from function createTextureFromString()" << std::endl;
        exit(EXIT_FAILURE);
    }
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, texture, NULL, &dest);

    SDL_DestroyTexture(texture);
}


std::string intToString(int i)
{
     std::ostringstream oss;
     oss << i;
     return oss.str();
}

std::string doubleToString(double d)
{
    std::ostringstream oss;
    oss << d;
    return oss.str();
}

