#include "Textures.h"

Textures::Textures()
{
}

Textures::~Textures()
{
}

SDL_Texture *const Textures::Load(const char *path)
{
    return nullptr;
}

bool Textures::UnLoad(SDL_Texture *texture)
{
    return false;
}

void Textures::GetSize(const SDL_Texture *texture, float &width, float &height) const
{
    SDL_GetTextureSize((SDL_Texture*)texture, &width, &height);
}
