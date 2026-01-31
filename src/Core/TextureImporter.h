#pragma once

#include "SDL3_image/SDL_image.h"
#include <list>
#include <string>

class TextureImporter
{
public:
    TextureImporter() = delete;
    ~TextureImporter() {}

    static SDL_Texture *const Load(std::string path);
    static void UnLoad(SDL_Texture *texture);

    void GetSize(const SDL_Texture *texture, float &width, float &height) const;

private:
    static SDL_Texture *const LoadSurface(SDL_Surface *surface);
};