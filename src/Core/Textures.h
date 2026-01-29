#pragma once

#include "SDL3_image/SDL_image.h"
#include <list>

class Textures
{
public:
    Textures();
    ~Textures();

    SDL_Texture *const Load(const char *path);
    bool UnLoad(SDL_Texture *texture);

    void GetSize(const SDL_Texture *texture, float &width, float &height) const;

private:
    std::list<SDL_Texture *> textures;
};