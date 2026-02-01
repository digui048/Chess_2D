#include "TextureImporter.h"
#include "Core/Log.h"
#include "Core/Application.h"

SDL_Texture *const TextureImporter::Load(std::string path)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = IMG_Load(path.c_str());

    if (surface == NULL)
    {
        Log::Warn("Could not load surface with path: {}. IMG_Load: {}", path, SDL_GetError());
    }
    else
    {
        texture = LoadSurface(surface);
        SDL_DestroySurface(surface);
    }

    return texture;
}

void TextureImporter::UnLoad(SDL_Texture *texture)
{
    Log::Info("Freeing texture...");
    SDL_DestroyTexture(texture);
}

void TextureImporter::GetSize(const SDL_Texture *texture, float &width, float &height) const
{
    SDL_GetTextureSize((SDL_Texture *)texture, &width, &height);
}

SDL_Texture *const TextureImporter::LoadSurface(SDL_Surface *surface)
{
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Application::GetInstance().GetRenderer()->GetRenderer(), surface);

    if (texture == NULL)
    {
        Log::Warn("Unable to create texture from surface! SDL Error: {}", SDL_GetError());
    }

    return texture;
}
